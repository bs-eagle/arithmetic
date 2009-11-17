/**
 *       \file  unary_operators.h
 *      \brief  implementation of unary operators
 *     \author  Sergey Miryanov (sergey-miryanov), sergey.miryanov@gmail.com
 *       \date  23.10.2009
 *  \copyright  This source code is released under the terms of 
 *              the BSD License. See LICENSE for more details.
 * */
#ifndef BS_ARCH_UNARY_OPERATORS_H_
#define BS_ARCH_UNARY_OPERATORS_H_

#include "arithmetic_iface.h"

namespace blue_sky {
namespace arch {

  /**
   * \class unary_operator
   * \brief base class of unary operators 
   *        inherits unary_operator_iface
   */
  struct unary_operator : unary_operator_iface
  {
    /**
     * \brief  unary_operator ctor
     * \param  rhs rhs operand
     * \return 
     */
    unary_operator (const shared_operand_t &rhs)
    : rhs (rhs)
    {
    }

    boost::shared_ptr <operand_iface> rhs; /**< @brief rhs operand */
  };

  /**
   * \class unary_minus_operator
   * \brief incapsulates unary minus operation
   *        implements unary_operator_iface
   */
  struct unary_minus_operator : unary_operator
  {
    /**
     * \brief  unary_minus_operator ctor
     * \param  rhs rhs operand
     */
    unary_minus_operator (const shared_operand_t &rhs) 
    : unary_operator (rhs)
    {
    }

    /**
     * \brief  returns negated value of rhs[idx] value
     * \param  idx value index in slice
     * \param  local_idx value index
     * \return negated value of rhs[idx]
     */
    float16_t
    get (long long idx, long long local_idx)
    {
      return -rhs->get (idx, local_idx);
    }
  };

  /**
   * \class log_op
   * \brief Incapsulates logarithm operation,
   *        implements unary_operator_iface
   * */
  struct log_op : unary_operator
  {
    /**
     * \brief  log_op ctor
     * \param  rhs rhs operand
     * */
    log_op (const shared_operand_t &rhs)
    : unary_operator (rhs)
    {
    }

    /**
     * \brief  Returns logarithm of rhs[idx] value
     * \param  idx value index in slice
     * \param  local_idx value index
     * \return Throws exception if rhs[idx] value is not positive,
     *         otherwise returns logarithm of this value
     * */
    float16_t
    get (long long idx, long long local_idx)
    {
      float16_t value = rhs->get (idx, local_idx);
      if (value > 0)
        {
          return ::log (value);
        }
      else
        {
          bs_throw_exception (boost::format ("Argument should be greater than zero (%ld, %ld)")
            % idx % local_idx);
        }
    }
  };
  /**
   * \class log10_op
   * \brief Incapsulates logarithm operation,
   *        implements unary_operator_iface
   * */
  struct log10_op : unary_operator
  {
    /**
     * \brief  log10_op ctor
     * \param  rhs rhs operand
     * */
    log10_op (const shared_operand_t &rhs)
    : unary_operator (rhs)
    {
    }

    /**
     * \brief  Returns logarithm10 of rhs[idx] value
     * \param  idx value index in slice
     * \param  local_idx value index
     * \return Throws exception if rhs[idx] value is not positive,
     *         otherwise returns logarithm10 of this value
     * */
    float16_t
    get (long long idx, long long local_idx)
    {
      float16_t value = rhs->get (idx, local_idx);
      if (value > 0)
        {
          return log10 (value);
        }
      else
        {
          bs_throw_exception (boost::format ("Argument should be greater than zero (%ld, %ld)")
            % idx % local_idx);
        }
    }
  };

#define UNARY_OP(name, op)              \
  struct name : unary_operator          \
  {                                     \
    name (const shared_operand_t &rhs)  \
    : unary_operator (rhs)              \
    {                                   \
    }                                   \
    float16_t                           \
    get (long long idx, long long lidx) \
    {                                   \
      return op (rhs->get (idx, lidx)); \
    }                                   \
  };

  UNARY_OP (sin_op,  sin);
  UNARY_OP (cos_op,  cos);
  UNARY_OP (tan_op,  tan);
  UNARY_OP (sqrt_op, sqrt);
  UNARY_OP (abs_op,  fabs);


} // namespace arch
} // namespace blue_sky

#endif // #ifndef BS_ARCH_UNARY_OPERATORS_H_

