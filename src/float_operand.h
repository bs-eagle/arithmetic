/**
 *       \file  float_operand.h
 *      \brief  implementation of float operand
 *     \author  Sergey Miryanov (sergey-miryanov), sergey.miryanov@gmail.com
 *       \date  23.10.2009
 *  \copyright  This source code is released under the terms of 
 *              the BSD License. See LICENSE for more details.
 * */
#ifndef BS_ARCH_FLOAT_OPERAND_H_
#define BS_ARCH_FLOAT_OPERAND_H_

#include "arithmetic_iface.h"

namespace blue_sky {
namespace arch {

  /**
   * \class float_operand
   * \brief stores float value, 
   *        implements float_operand_iface
   */
  struct float_operand : float_operand_iface
  {
    /**
     * \brief  float_operand ctor
     * \param  value stored value
     * \return 
     */
    float_operand (float16_t value)
    : value_ (value)
    {
    }

    /**
     * \brief  obsolete, deprecated
     * \param  
     * \return 
     */
    void
    set (float16_t value)
    {
      value_ = value;
    }

    /**
     * \brief  returns stored value
     * \param  __formal
     * \param  __formal
     * \return stored value
     */
    float16_t
    get (long long, long long)
    {
      return value_;
    }

    float16_t value_; /**< @brief stored value */
  };


} // namespace arch
} // namespace blue_sky

#endif // #ifndef BS_ARCH_FLOAT_OPERAND_H_

