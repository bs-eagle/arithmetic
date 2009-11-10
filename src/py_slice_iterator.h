/**
 *       \file  py_slice_iterator.h
 *      \brief  export to python slice and slice_iterator
 *     \author  Sergey Miryanov (sergey-miryanov), sergey.miryanov@gmail.com
 *       \date  26.10.2009
 *  \copyright  This source code is released under the terms of 
 *              the BSD License. See LICENSE for more details.
 * */
#ifndef BS_ARCH_PY_SLICE_ITERATOR_H_
#define BS_ARCH_PY_SLICE_ITERATOR_H_

#include "arithmetic_iface.h"

namespace blue_sky {
namespace arch {
namespace python {

  /**
   * \class py_slice_iterator <strategy_t>
   * \brief incapsulates arithmetic expression evaluation 
   * */
  template <typename strategy_t>
  struct py_slice_iterator 
  {
    /**
     * \brief  iterates through data in slice range, 
     *         evaluates expression top and stores result 
     *         of it in float dest array
     * \param  s slice that stores info of data range
     * \param  dest destination array, result of 
     *              expression will be stored in this array
     * \param  top top of the expression tree, expression 
     *             will be evaluated from top to bottom of 
     *             tree
     * \return 
     * */
    void
    iterate_slice_float (const slice &s, array_float16_t &dest, const shared_operand_t &top);

    /**
     * \brief  iterates through data in slice range, 
     *         evaluates expression top and stores result 
     *         of it in integer dest array
     * \param  s slice that stores info of data range
     * \param  dest destination array, result of 
     *              expression will be stored in this array
     * \param  top top of the expression tree, expression 
     *             will be evaluated from top to bottom of 
     *             tree
     * \return 
     * */
    void
    iterate_slice_int (const slice &s, array_uint8_t &dest, const shared_operand_t &top);
  };

  /**
   * \brief  exports python wrappers for slice and py_slice_iterator
   * \param  
   * \return 
   * */
  void
  export_slice_iterator ();

} // namespace python
} // namespace arch
} // namespace blue_sky

#endif // #ifndef BS_ARCH_PY_SLICE_ITERATOR_H_

