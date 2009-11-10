/**
 *       \file  py_arithmetic_iface.h
 *      \brief  python wrapper for arithmetic_iface class
 *     \author  Sergey Miryanov (sergey-miryanov), sergey.miryanov@gmail.com
 *       \date  27.10.2009
 *  \copyright  This source code is released under the terms of 
 *              the BSD License. See LICENSE for more details.
 * */
#ifndef BS_ARCH_PY_ARITHMETIC_IFACE_H_
#define BS_ARCH_PY_ARITHMETIC_IFACE_H_

#include "arithmetic_iface.h"
#include "strategies.h"
#include "export_python_wrapper.h"

namespace blue_sky {
namespace arch {
namespace python {

  /**
   * \class py_arithmetic_iface_base
   * \brief dummy class to avoid compilation error
   * */
  struct py_arithmetic_iface_base : arithmetic_iface
  {
  };
  /**
   * \class py_arithmetic_iface
   * \brief python wrapper for arithmetic_iface
   *        implements arithmetic_iface
   * \detail if arithmetic_iface implemented if python try
   *         to call interface function otherwise throws
   *         exception
   * */
  struct py_arithmetic_iface : py_arithmetic_iface_base, boost::python::wrapper <py_arithmetic_iface_base>
  {
    /**
     * \brief  py_arithmetic_iface ctor
     * \param  
     * \return 
     * */
    py_arithmetic_iface ()
    {
    }
    /**
     * \brief  py_arithmetic_iface copy ctor
     * \param  
     * \return 
     * */
    py_arithmetic_iface (const py_arithmetic_iface_base &)
    {
    }

    /**
     * \brief  process arithmetic expression
     * \param  line string with arithmetic expression
     * \return may throw exception
     */
    WRAP_PURE_METHOD (process_line, void, 1, (const std::string &));
  };

  /**
   * \brief  exports arithmetic_iface and py_arithmetic_iface to python
   * \param  
   * \return 
   * */
  void
  export_arithmetic_iface ()
  {
    using namespace boost::python;
    class_ <arithmetic_iface, boost::noncopyable> ("arithmetic_iface", no_init)
      .def ("process_line", &arithmetic_iface::process_line)
      ;

    class_ <py_arithmetic_iface, bases <arithmetic_iface> > ("py_arithmetic_iface")
      .def ("process_line", &py_arithmetic_iface::process_line)
      ;
  }

} // namespace python
} // namespace arch
} // namespace blue_sky

#endif // #ifndef BS_ARCH_PY_ARITHMETIC_IFACE_H_

