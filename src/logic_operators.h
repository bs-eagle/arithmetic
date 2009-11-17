#ifndef BS_ARCH_LOGIC_OPERATORS_H_
#define BS_ARCH_LOGIC_OPERATORS_H_

#include "binary_operators.h"

namespace blue_sky {
namespace arch {

#define LOGIC_OP(name, op)                                                  \
  struct name : binary_operator                                             \
  {                                                                         \
    name (const shared_operand_t &lhs, const shared_operand_t &rhs)         \
    : binary_operator (lhs, rhs)                                            \
    {                                                                       \
    }                                                                       \
    float16_t                                                               \
    get (long long idx, long long local_idx)                                \
    {                                                                       \
      return lhs->get (idx, local_idx) op rhs->get (idx, local_idx);        \
    }                                                                       \
  };

  LOGIC_OP (greater_op,     >);
  LOGIC_OP (greater_equ_op, >=);
  LOGIC_OP (less_op,        <);
  LOGIC_OP (less_equ_op,    <=);
  LOGIC_OP (equ_op,         ==);
  LOGIC_OP (not_equ_op,     !=);


} // namespace arch
} // namespace blue_sky


#endif // #ifndef BS_ARCH_LOGIC_OPERATORS_H_

