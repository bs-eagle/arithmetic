import bs
import arch_grammar as ag

class bs_f :
    def __init__ (self) :
        self.list = {
                "max"       : (ag.grammar.is_equ, ag.grammar.binary_op,     bs.bs_arch.max_op)
                , "min"     : (ag.grammar.is_equ, ag.grammar.binary_op,     bs.bs_arch.min_op)
                , "+"       : (ag.grammar.is_equ, ag.grammar.binary_op,     bs.bs_arch.sum_op)
                , "-"       : (ag.grammar.is_equ, ag.grammar.binary_op,     bs.bs_arch.sub_op)
                , "*"       : (ag.grammar.is_equ, ag.grammar.binary_op,     bs.bs_arch.mul_op)
                , "/"       : (ag.grammar.is_equ, ag.grammar.binary_op,     bs.bs_arch.div_op)

                , "un"      : (ag.grammar.is_equ, ag.grammar.unary_op,      bs.bs_arch.unary_minus_op)
                , "sin"     : (ag.grammar.is_equ, ag.grammar.unary_op,      bs.bs_arch.sin_op)
                , "cos"     : (ag.grammar.is_equ, ag.grammar.unary_op,      bs.bs_arch.cos_op)
                , "tan"     : (ag.grammar.is_equ, ag.grammar.unary_op,      bs.bs_arch.tan_op)
                , "sqrt"    : (ag.grammar.is_equ, ag.grammar.unary_op,      bs.bs_arch.sqrt_op)
                , "abs"     : (ag.grammar.is_equ, ag.grammar.unary_op,      bs.bs_arch.abs_op)
                , "log"     : (ag.grammar.is_equ, ag.grammar.unary_op,      bs.bs_arch.log_op)
                , "log10"   : (ag.grammar.is_equ, ag.grammar.unary_op,      bs.bs_arch.log10_op)

                , "DX"      : (ag.grammar.is_equ, ag.grammar.float_array,   bs.bs_arch.array_op)
                , "DY"      : (ag.grammar.is_equ, ag.grammar.float_array,   bs.bs_arch.array_op)
                , "DZ"      : (ag.grammar.is_equ, ag.grammar.float_array,   bs.bs_arch.array_op)
                , "PERMX"   : (ag.grammar.is_equ, ag.grammar.float_array,   bs.bs_arch.array_op)
                , "PERMY"   : (ag.grammar.is_equ, ag.grammar.float_array,   bs.bs_arch.array_op)
                , "PERMZ"   : (ag.grammar.is_equ, ag.grammar.float_array,   bs.bs_arch.array_op)
                , "TOPS"    : (ag.grammar.is_equ, ag.grammar.float_array,   bs.bs_arch.array_op)
                , "PORO"    : (ag.grammar.is_equ, ag.grammar.float_array,   bs.bs_arch.array_op)
                , "SOIL"    : (ag.grammar.is_equ, ag.grammar.float_array,   bs.bs_arch.array_op)
                , "SWAT"    : (ag.grammar.is_equ, ag.grammar.float_array,   bs.bs_arch.array_op)
                , "PRESSURE": (ag.grammar.is_equ, ag.grammar.float_array,   bs.bs_arch.array_op)
                , "MULTX"   : (ag.grammar.is_equ, ag.grammar.float_array,   bs.bs_arch.array_op)
                , "MULTY"   : (ag.grammar.is_equ, ag.grammar.float_array,   bs.bs_arch.array_op)
                , "MULTZ"   : (ag.grammar.is_equ, ag.grammar.float_array,   bs.bs_arch.array_op)
                , "PERMXY"  : (ag.grammar.is_equ, ag.grammar.float_array,   bs.bs_arch.array_op)

                , "ACTNUM"  : (ag.grammar.is_equ, ag.grammar.int_array,     bs.bs_arch.array_op)
                , "BNDNUM"  : (ag.grammar.is_equ, ag.grammar.int_array,     bs.bs_arch.array_op)
                , "EQLNUM"  : (ag.grammar.is_equ, ag.grammar.int_array,     bs.bs_arch.array_op)
                , "FIPNUM"  : (ag.grammar.is_equ, ag.grammar.int_array,     bs.bs_arch.array_op)
                , "SATNUM"  : (ag.grammar.is_equ, ag.grammar.int_array,     bs.bs_arch.array_op)
                , "PVTNUM"  : (ag.grammar.is_equ, ag.grammar.int_array,     bs.bs_arch.array_op)

                , "vop"     : (ag.grammar.is_equ, self.vector_op,           bs.bs_arch.vector_op)
                , "iif"     : (ag.grammar.is_equ, self.ternary_op,          bs_f.iif_op)

                , ">"       : (ag.grammar.is_equ, ag.grammar.binary_op,     bs.bs_arch.greater_op)
                , ">="      : (ag.grammar.is_equ, ag.grammar.binary_op,     bs.bs_arch.greater_equ_op)
                , "<"       : (ag.grammar.is_equ, ag.grammar.binary_op,     bs.bs_arch.less_op)
                , "<="      : (ag.grammar.is_equ, ag.grammar.binary_op,     bs.bs_arch.less_equ_op)
                , "=="      : (ag.grammar.is_equ, ag.grammar.binary_op,     bs.bs_arch.equ_op)
                , "!="      : (ag.grammar.is_equ, ag.grammar.binary_op,     bs.bs_arch.not_equ_op)
                }

    def vector_op (self, g, d, f, name, op) :
        s = g.vector.pop ()
        v = bs.bs_bos_core_data_storage.array_ext_f ()
        v.resize (len (s), 0)
        for i in xrange (0, len (s)) :
            v[i] = float (s[i])

        return op (v)

    def ternary_op (self, g, ds, f, name, op) :
        f_ = g.build_tree (ds, f)
        t_ = g.build_tree (ds, f)
        c_ = g.build_tree (ds, f)

        return op (c_, t_, f_)

    class iif_op (bs.bs_arch.py_operand_iface) :
        def __init__ (self, cond, true_exp, false_exp) :
            bs.bs_arch.py_operand_iface.__init__ (self)
            self.cond = cond
            self.true_exp = true_exp
            self.false_exp = false_exp

        def get (self, idx, lidx) :
            if (self.cond.get (idx, lidx) <> 0) :
                return self.true_exp.get (idx, lidx)
            else :
                return self.false_exp.get (idx, lidx)


    def handle_operation (self, g, ds, op) :

        for name, (equ, ctor, type) in self.list.items () :
            if (equ (g, name, op)) :
                return ctor (g, ds, self, op, type)

        if (ag.grammar.is_float (g, op)) :
            return ag.grammar.float_op (g, ds, self, op, bs.bs_arch.float_op)
        elif (ag.grammar.is_int (g, op)) :
            return ag.grammar.int_op (g, ds, self, op, bs.bs_arch.int_op)
        else :
            raise Exception ("\tNo action found for: %s" % (op))

    def get_array (self, ds, n) :
        for name, (_, ctor, _) in self.list.items () :
            if (name == n and ctor == ag.grammar.float_array) :
                return ds.get_float_array (name)
            elif (name == n and ctor == ag.grammar.int_array) :
                return ds.get_int_arry (name)

        return None

    def evaluate (self, top, slice, ds, array) :
        pnt = bs.bs_arch.slice_point
        s = bs.bs_arch.slice (pnt (slice.x.begin, slice.x.end), pnt (slice.y.begin, slice.y.end), pnt (slice.z.begin, slice.z.end))

        bs.bs_arch.slice_iterator ().iterate_slice (s, ds.dimens, array, top);

