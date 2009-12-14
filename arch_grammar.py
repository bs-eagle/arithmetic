from pyparsing import *
import re, math, operator, time

class grammar :

    def grammar (self) :
        class range_node :
            def __init__ (self, begin, end) :
                self.begin = begin
                self.end = end
            def __str__ (self) :
                return "%d:%d" % (self.begin, self.end)
            def __repr__ (self) :
                return self.__str__ ()

        class slice_node :
            def __init__ (self, slice) :
                self.x = slice[0] if len (slice) > 0 else range_node (0, -1)
                self.y = slice[1] if len (slice) > 1 else range_node (0, -1)
                self.z = slice[2] if len (slice) > 2 else range_node (0, -1)
            def __str__ (self) :
                return "(%s, %s, %s)" % (self.x.__str__ (), self.y.__str__ (), self.z.__str__ ())
            def __repr__ (self) :
                return self.__str__ ()

        class name_node :
            def __init__ (self, name) :
                self.name = name
            def __str__ (self) :
                return self.name
            def __repr__ (self) :
                return self.__str__ ()

        class dst_node :
            def __init__ (self, data) :
                self.name = str (data[0])
                self.slice = data[1] if len (data) > 1 else slice_node ([])
            def __str__ (self) :
                return "%s%s" % (self.name, self.slice)
            def __repr__ (self) :
                return self.__str__ ()

        class expression_node :
            def __init__ (self, expression) :
                self.expression = expression
            def __str__ (self) :
                return "%s" % (self.expression)
            def __repr__ (self) :
                return self.__str__ ()

        plus        = Literal ('+')
        minus       = Literal ('-')
        mult        = Literal ('*')
        div         = Literal ('/')
        lpar        = Literal ('(').suppress ()
        rpar        = Literal (')').suppress ()
        comma       = Literal (",")
        two_dot     = Literal (":")
        equal       = Literal ("=").suppress ()
        unary_minus = Literal ('-')
        slpar       = Literal ("[").suppress ()
        srpar       = Literal ("]").suppress ()
        gr          = Literal (">")
        gr_equ      = Combine (Literal (">") + Literal ("="))
        ls          = Literal ("<")
        ls_equ      = Combine (Literal ("<") + Literal ("="))
        equ         = Combine (Literal ("=") + Literal ("="))
        not_equ     = Combine (Literal ("!") + Literal ("="))

        number      = Word (nums)
        keyword     = Word (alphas)
        integer     = Word (nums)

        addop       = plus | minus
        mulop       = mult | div
        logicop     = gr | gr_equ | ls | ls_equ | equ | not_equ

        factor      = Forward ()
        term        = Forward ()
        expr        = Forward ()
        mul_term    = Forward ()
        add_expr    = Forward ()
        logic       = Forward ()
        logic_2     = Forward ()
        rhs         = Forward ()

        vector_item = Word (nums)

        group       = lpar + rhs + rpar
        fun         = Combine (Word (alphas) + ZeroOrMore (Word (nums))) + lpar + rhs + ZeroOrMore (comma + rhs) + rpar
        vector      = slpar + vector_item + ZeroOrMore (comma.suppress () + vector_item) + srpar
        atom        = fun | keyword | number

        factor      << (Optional (unary_minus) + (atom | vector | group))
        mul_term    << (mulop + factor)
        term        << (factor + ZeroOrMore (mul_term))
        add_expr    << (addop + term)
        expr        << (term + ZeroOrMore (add_expr))
        logic_2     << (logicop + expr)
        logic       << (expr + ZeroOrMore (logic_2))
        rhs         << logic

        range       = (integer + two_dot + integer)
        range_comma = (comma + range)
        slice       = (lpar + range + Optional (range_comma) + Optional (range_comma) + rpar)
        name        = (Word (alphas))
        dst         = (name + Optional (slice))

        top         = dst + equal + rhs

        def un (t) :
            if (t and t[0] == '-') :
                self.stack.append ("un")

        def set_dest (t) :
            self.dest = dst_node (t)
            return self.dest

        def vop (t) :
            self.stack.append ("vop")
            self.vector.append (t)

        range.setParseAction        (lambda s, l, toks: range_node (int (toks[0]), int (toks[2])))
        range_comma.setParseAction  (lambda s, l, toks: toks[1])
        slice.setParseAction        (lambda s, l, toks: slice_node (toks))
        name.setParseAction         (lambda s, l, toks: name_node (toks[0]))
        dst.setParseAction          (lambda s, l, toks: set_dest (toks))
        expr.setParseAction         (lambda s, l, toks: expression_node (toks[0]))

        mul_term.setParseAction     (lambda s, l, t: self.stack.append (t[0]))
        add_expr.setParseAction     (lambda s, l, t: self.stack.append (t[0]))
        atom.setParseAction         (lambda s, l, t: self.stack.append (t[0]))
        factor.setParseAction       (lambda s, l, t: un (t))
        logic_2.setParseAction      (lambda s, l, t: self.stack.append (t[0]))

        vector.setParseAction       (lambda s, l, t: vop (t))

        return top

    def __init__ (self) :

        self.stack              = []
        self.vector             = []
        self.top                = self.grammar ()
        self.array_handler      = None
        self.binary_handler     = None
        self.unary_handler      = None
        self.before_evaluate    = None
        self.normalize_slice    = self.default_slice_normalization

    def default_slice_normalization (self, ds, slice) :
        if (slice.x.end == -1) :
            slice.x.end = ds.nx - 1
        if (slice.y.end == -1) :
            slice.y.end = ds.ny - 1
        if (slice.z.end == -1) :
            slice.z.end = ds.nz - 1

    def binary_op (g, ds, f, name, op) :
        rhs = g.build_tree (ds, f)
        lhs = g.build_tree (ds, f)
        return op (lhs, rhs)

    def unary_op (g, ds, f, name, op) :
        rhs = g.build_tree (ds, f)
        return op (rhs)

    def float_array (g, ds, f, name, op) :
        if (g.array_handler is not None) :
            g.array_handler (name, ds.get_float_array (name))

        return op (ds.get_float_array (name))

    def int_array (g, ds, f, name, op) :
        if (g.array_handler is not None) :
            g.array_handler (name, ds.get_int_array (name))

        return op (ds.get_int_array (name))

    def float_op (g, ds, f, name, op) :
        return op (float (name))

    def int_op (g, ds, f, name, op) :
        return op (int (name))

    def is_equ (self, lhs, rhs) :
        return lhs.lower () == rhs.lower ()

    def is_float (self, lhs) :
        float_re = re.compile ("\d+\.*\d*")
        return float_re.match (lhs) <> None

    def is_int (self, lhs) :
        int_re = re.compile ("\d+")
        return int_re.match (lhs) <> None

    def parse (self, str) :
        self.stack = []
        self.vector = []
        self.dest = None
        self.top.parseString (str)

        if (self.dest is None) :
            raise Exception ("Parsed string doesn't contain dest")

        return self.dest.slice

    def build_tree (self, ds, f) :
        return f.handle_operation (self, ds, self.stack.pop ())

    def evaluate (self, ds, f, str) :
        try :
            slice   = self.parse (str)
            top     = self.build_tree (ds, f)
            dest    = f.get_array (ds, self.dest.name)

            if (dest is None) :
                raise Exception ("Destination array is unknown %s" % (self.dest.name))

            if (self.array_handler is not None) :
                self.array_handler (self.dest.name, dest)

            if (self.normalize_slice is not None) :
                self.normalize_slice (ds, slice)

            if (self.before_evaluate is not None) :
                self.before_evaluate ()

            f.evaluate (top, slice, ds, dest)
        except Exception as ex:
            print ("Following errors occured while parsing line %s: \n%s" % (str, ex))

class data_source :

    class triple :
        def __init__ (self, x, y, z) :
            self.x = x
            self.y = y
            self.z = z

        def __str__ (self) :
            return "(%d, %d, %d)" % (self.x, self.y, self.z)
        def __repr__ (self) :
            return self.__str__ ()

    class dims_ :
        def __init__ (self, x, y, z) :
            self.begin = data_source.triple (0, 0, 0)
            self.end = data_source.triple (x, y, z)

        def __str__ (self) :
            return "(%d:%d, %d:%d, %d:%d)" % (self.begin.x, self.end.x, self.begin.y, self.end.y, self.begin.z, self.end.z)
        def __repr__ (self) :
            return self.__str__ ()

    def __init__ (self, x, y, z) :
        self.dims = data_source.dims_ (x, y, z)
        self.arrays = dict ()

    def get (self, key) :
        return self.arrays[key]

    def __getitem__ (self, key) :
        return self.get (key)

    def get_index (self, i, j, k) :
        return i * self.dims.end.x * self.dims.end.y + j * self.dims.end.x + k

    def add_array (self, name, a) :
        for i in xrange (self.dims.end.x) :
            for j in xrange (self.dims.end.y) :
                for k in xrange (self.dims.end.z) :
                    idx = self.get_index (i, j, k)
                    a.append (0)

        self.arrays[name] = a

    def get_nx (self) :
        return self.dims.end.x
    def get_ny (self) :
        return self.dims.end.y
    def get_nz (self) :
        return self.dims.end.z

    nx = property (get_nx)
    ny = property (get_ny)
    nz = property (get_nz)

class functors :
    def __init__ (self) :

        def unary_minus_op (lhs) :
            return -lhs

        class dummy_op :
            def __init__ (self, rhs) :
                pass

        class unary_op :
            def __init__ (self, op, rhs) :
                self.op = op
                self.rhs = rhs

            def __str__ (self) :
                return "(%s %s)" % (str (self.op), self.rhs)
            def __repr__ (self) :
                return self.__str__ ()

            def get (self, idx) :
                return self.op (self.rhs.get (idx))

        class binary_op :
            def __init__ (self, op, lhs, rhs) :
                self.op = op
                self.lhs = lhs
                self.rhs = rhs

            def __str__ (self) :
                return "(%s %s %s)" % (str (self.op), self.lhs, self.rhs)

            def __repr__ (self) :
                return self.__str__ ()

            def get (self, idx) :
                return self.op (self.lhs.get (idx), self.rhs.get (idx))

        class array_max_op (binary_op) :
            def __init__ (self, lhs, rhs) :
                binary_op.__init__ (self, max, lhs, rhs)

        class array_min_op (binary_op) :
            def __init__ (self, lhs, rhs) :
                binary_op.__init__ (self, min, lhs, rhs)

        class array_sum_op (binary_op) :
            def __init__ (self, lhs, rhs) :
                binary_op.__init__ (self, operator.add, lhs, rhs)

        class array_sub_op (binary_op) :
            def __init__ (self, lhs, rhs) :
                binary_op.__init__ (self, operator.sub, lhs, rhs)

        class array_mul_op (binary_op) :
            def __init__ (self, lhs, rhs) :
                binary_op.__init__ (self, operator.mul, lhs, rhs)

        class array_div_op (binary_op) :
            def __init__ (self, lhs, rhs) :
                binary_op.__init__ (self, operator.div, lhs, rhs)

        class array_minus_op (unary_op) :
            def __init__ (self, rhs) :
                unary_op.__init__ (self, unary_minus_op, rhs)

        class array_operand :
            def __init__ (self, array) :
                self.array = array

            def __str__ (self) :
                return self.name
            def __repr__ (self) :
                return self.__str__ ()

            def get (self, idx) :
                return self.array[idx]

        class float_operand :
            def __init__ (self, value) :
                self.value = value

            def __str__ (self) :
                return str (self.value)
            def __repr__ (self) :
                return self.__str__ ()

            def get (self, idx) :
                return self.value

        self.binary = {
                "max"   : array_max_op,
                "min"   : array_min_op,
                "+"     : array_sum_op,
                "-"     : array_sub_op,
                "*"     : array_mul_op,
                "/"     : array_div_op
                }
        self.unary = {
                "un"    : array_minus_op
#                "log"   : dummy_op,
#                "log10" : dummy_op,
#                "exp"   : dummy_op,
#                "sin"   : dummy_op,
#                "cos"   : dummy_op,
#                "tan"   : dummy_op,
#                "sqrt"  : dummy_op,
#                "abs"   : dummy_op
                }
        self.float_arrays = {
                "PORO"  : array_operand , 
                "PERM"  : array_operand , 
                "SWAT"  : array_operand 
                }
        self.int_arrays = {
                "ACTNUM"    : array_operand
                }

        self.float_op = float_operand
        self.int_op = dummy_op

class naive_f (functors) :
    def __init__ (self) :
        functors.__init__ (self)

    def evaluate (self, top, slice, ds, array) :
        for i in xrange (slice.x.begin, slice.x.end) :
            for j in xrange (slice.y.begin, slice.y.end) :
                for k in xrange (slice.z.begin, slice.z.end) :
                    idx = ds.get_index (i, j, k)
                    array[idx] = top.get (idx)

class unrolled_naive_f (functors) :
    def __init__ (self) :
        functors.__init__ (self)

    def evaluate (self, top, slice, ds, array) :
        for i in xrange (slice.x.begin, slice.x.end) :
            for j in xrange (slice.y.begin, slice.y.end) :
                k_ = 0
                for k in xrange (slice.z.begin, slice.z.end, 2) :
                    idx = ds.get_index (i, j, k)
                    array[idx] = top.get (idx)
                    idx = ds.get_index (i, j, k + 1)
                    array[idx] = top.get (idx)
                    k_ = k

                if (k_ <> slice.z.end) :
                    for k in xrange (k_, slice.z.end) :
                        idx = ds.get_index (i, j, k)
                        array[idx] = top.get (ds, idx)


def test (f, str) :
    g = grammar ()
    ds = data_source (100, 100, 100)


    start = time.clock ()
    ds.add_array ("PORO")


    middle = time.clock ()
    g.evaluate (ds, f, str)
    end = time.clock ()

    print ("add: ", middle-start)
    print ("eval: ", end-middle)

#test (bs_f (), "PORO = 1")
#test (naive_f (), "PORO = 2")
#test (unrolled_naive_f (), "PORO = 3")
