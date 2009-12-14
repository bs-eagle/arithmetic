/**
 *       \file  bs_arch_main.cpp
 *      \brief  main file for binary part of arithmetic plugin
 *     \author  Sergey Miryanov (sergey-miryanov), sergey.miryanov@gmail.com
 *       \date  23.10.2009
 *  \copyright  This source code is released under the terms of 
 *              the BSD License. See LICENSE for more details.
 * */
#include "bs_common.h"
#include "bs_kernel.h"
#include "bs_object_base.h"
#include <boost/array.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "bs_assert.h"

#include "binary_operators.h"
#include "unary_operators.h"
#include "float_operand.h"
#include "array_operand.h"
#include "vector_operand.h"
#include "logic_operators.h"

#include "py_slice_iterator.h"
#include "py_arithmetic_iface.h"
#include "py_operand_iface.h"

using namespace blue_sky;
using namespace blue_sky::python;
using namespace boost::python;
using namespace boost;

namespace blue_sky {
  BLUE_SKY_PLUGIN_DESCRIPTOR_EXT ("bs_arch", "1.0.0", "BS_ARITHMETIC", "BS_ARITHMETIC", "bs_arch")

  BLUE_SKY_REGISTER_PLUGIN_FUN
  {
    //const plugin_descriptor &pd = *bs_init.pd_;

    bool res = true;
    return res;
  }
}

/**
 * \brief  exports unary operator to python
 * \param  name name of exported wrapper
 * \return 
 * */
template <typename T>
void
export_unary (const char *name)
{
  using namespace blue_sky::arch;
  class_ <T, bases <operand_iface> > (name, init <shared_ptr <operand_iface> > ())
    .def ("get", &T::get)
    ;
}

/**
 * \brief  exports binary operator to python
 * \param  name name of exported wrapper
 * \return 
 * */
template <typename T>
void
export_binary (const char *name)
{
  using namespace blue_sky::arch;
  class_ <T, bases <arch::operand_iface> > (name, init <shared_ptr <operand_iface>, shared_ptr <operand_iface> > ())
    .def ("get", &T::get)
    ;
}

#ifdef BSPY_EXPORTING_PLUGIN
BLUE_SKY_INIT_PY_FUN
{
  using namespace arch;
  using namespace arch::python;

  export_operand_iface ();

  class_ <float_operand, bases <operand_iface> > ("float_op", init <double> ())
    .def ("get", &float_operand::get)
    .add_property ("value", &float_operand::value_)
    ;

  class_ <array_operand, bases <operand_iface> > ("array_op", init <const array_float16_t &> ())
    .def ("get", &array_operand::get)
    ;

  class_ <vector_operand, bases <operand_iface> > ("vector_op", init <const array_float16_t &> ())
    .def ("get", &array_operand::get)
    ;

  export_unary <unary_minus_operator> ("unary_minus_op");
  export_unary <sin_op>   ("sin_op");
  export_unary <cos_op>   ("cos_op");
  export_unary <tan_op>   ("tan_op");
  export_unary <sqrt_op>  ("sqrt_op");
  export_unary <abs_op>   ("abs_op");
  export_unary <log_op>   ("log_op");
  export_unary <log10_op> ("log10_op");

  export_binary <max_operator> ("max_op");
  export_binary <min_operator> ("min_op");
  export_binary <sum_operator> ("sum_op");
  export_binary <sub_operator> ("sub_op");
  export_binary <mul_operator> ("mul_op");
  export_binary <div_operator> ("div_op");

  export_binary <greater_op>      ("greater_op");
  export_binary <greater_equ_op>  ("greater_equ_op");
  export_binary <less_op>         ("less_op");
  export_binary <less_equ_op>     ("less_equ_op");
  export_binary <equ_op>          ("equ_op");
  export_binary <not_equ_op>      ("not_equ_op");

  export_slice_iterator ();
  export_arithmetic_iface ();
}
#endif // #ifdef BSPY_EXPORTING_PLUGIN

