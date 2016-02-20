#ifndef MRB_UNBOUND_RESULT_H
#define MRB_UNBOUND_RESULT_H

#include "mruby.h"
#include "unbound.h"

void mrb_define_unbound_result(mrb_state *mrb);
mrb_value mrb_result_iv_set(mrb_state *mrb, mrb_value value, struct ub_result *result);
#endif
