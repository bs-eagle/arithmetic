/**
 *       \file  array_operand.h
 *      \brief  implementation of array_operand_iface
 *     \author  Sergey Miryanov (sergey-miryanov), sergey.miryanov@gmail.com
 *       \date  23.10.2009
 *  \copyright  This source code is released under the terms of 
 *              the BSD License. See LICENSE for more details.
 * */
#ifndef BS_ARCH_ARRAY_OPERAND_H_
#define BS_ARCH_ARRAY_OPERAND_H_

#include "arithmetic_iface.h"

namespace blue_sky {
namespace arch {

  /**
   * \class array_operand
   * \brief implementation of array_operand_iface
   */
  struct array_operand : array_operand_iface
  {
    /**
     * \brief  array_operand constructor
     * \param  array handled array
     */
    array_operand (const array_float16_t &array)
    : array (array)
    {
    }

    /**
     * \brief  returns array[idx] value
     * \param  idx value index
     * \param  __formal
     * \return array[idx] value
     */
    float16_t
    get (long long idx, long long)
    {
      return array[idx];
    }

    array_float16_t array; /**< @brief handled array */
  };

} // namespace arch
} // namespace blue_sky

#endif // #ifndef BS_ARCH_ARRAY_OPERAND_H_

