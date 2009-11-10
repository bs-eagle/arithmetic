/**
 *       \file  py_operand_iface.h
 *      \brief  python wrapper for operand_iface
 *     \detail  python wrapper should be used to implement
 *              operand_iface in python
 *     \author  Sergey Miryanov (sergey-miryanov), sergey.miryanov@gmail.com
 *       \date  30.10.2009
 *  \copyright  This source code is released under the terms of 
 *              the BSD License. See LICENSE for more details.
 * */
#ifndef BS_ARCH_PY_OPERAND_IFACE_H_
#define BS_ARCH_PY_OPERAND_IFACE_H_

#include "arithmetic_iface.h"
#include "strategies.h"
#include "export_python_wrapper.h"

namespace blue_sky {
namespace arch {
namespace python {

  /**
   * \class py_operand_iface_base
   * \brief dummy class to avoid comilation errors
   * */
  struct py_operand_iface_base : operand_iface
  {
  };
  /**
   * \class py_operand_iface
   * \brief python wrapper for operand_iface
   *        implements operand_iface
   * \detail if operand_iface implemented in python try 
   *         to call interface function otherwise throws
   *         exception
   * */
  struct py_operand_iface : py_operand_iface_base, boost::python::wrapper <py_operand_iface_base>
  {
    /**
     * \brief  returns value with index
     * \param  idx is an index of value
     * \return may throw exception
     */
    WRAP_PURE_METHOD (get, float16_t, 1, (size_t));
  };

  /**
   * \brief  exports operand_iface and py_operand_iface to python
   * \param  
   * \return 
   * */
  void
  export_operand_iface ()
  {
    using namespace boost::python;

    class_ <operand_iface, boost::noncopyable> ("operand_iface", no_init)
      ;

    class_ <py_operand_iface, bases <operand_iface>, boost::noncopyable> ("py_operand_iface")
      .def ("get", &py_operand_iface::get)
      ;
  }

} // namespace python
} // namespace arch
} // namespace blue_sky

#endif // #ifndef BS_ARCH_PY_OPERAND_IFACE_H_
