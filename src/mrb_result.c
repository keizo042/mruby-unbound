#include "mruby.h"
#include "mruby/class.h"
#include "mruby/object.h"
#include "mruby/value.h"
#include "mruby/variable.h"
#include "mruby/array.h"

#include "unbound.h"

#include <arpa/inet.h>

mrb_value mrb_unbound_result_initialize(mrb_state *mrb, mrb_value self)
{
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "qname"),        mrb_str_new_cstr(mrb,""));
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "qtype"),        mrb_fixnum_value(0) );
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "qclass"),       mrb_fixnum_value(0) );
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "rcode"),        mrb_fixnum_value(0) );
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "havedata"),     mrb_fixnum_value(0));
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "nxdomain"),     mrb_fixnum_value(0));
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "secure"),       mrb_fixnum_value(0));
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "bogus"),        mrb_fixnum_value(0));
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "why_bogus"),   mrb_str_new_cstr(mrb, ""));
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "ttl"),          mrb_fixnum_value(0));
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "answer"),       mrb_str_new_cstr(mrb, ""));

    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "data"),         mrb_ary_new(mrb) );
    return self;
}
void mrb_define_unbound_result(mrb_state *mrb) 
{
    struct RClass *result, *unbound;
    unbound = mrb_class_get(mrb, "Unbound");

    result = mrb_define_class_under(mrb, unbound, "Result", mrb->object_class);

    mrb_define_method(mrb, result, "initialize", mrb_unbound_result_initialize, MRB_ARGS_REQ(1) );
}

mrb_value mrb_result_iv_set(mrb_state *mrb, mrb_value self, struct ub_result *result) 
{
    int i = 0;
    char **p;
    mrb_value data;

    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "qname"),        mrb_str_new_cstr(mrb,result->qname));
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "qtype"),        mrb_fixnum_value(result->qtype) );
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "qclass"),       mrb_fixnum_value(result->qclass) );
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "rcode"),        mrb_fixnum_value(result->rcode) );
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "havedata"),     mrb_fixnum_value(result->havedata));
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "nxdomain"),     mrb_fixnum_value(result->nxdomain));
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "secure"),       mrb_fixnum_value(result->secure));
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "bogus"),        mrb_fixnum_value(result->bogus));
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "why_bogus"),   mrb_str_new_cstr(mrb, result->why_bogus));
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "ttl"),          mrb_fixnum_value(result->ttl));

    data = mrb_ary_new(mrb);
    for(p = result->data; *p != NULL; p++)
    {
        mrb_ary_push(mrb, data, mrb_str_new_cstr(mrb, inet_ntoa( *(struct in_addr*)*p)) );
    }
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "data"),         data);

    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "answer"),       mrb_str_new(mrb, result->answer_packet, result->answer_len));

    return self;
}
