#include "mruby.h"
#include "mruby/class.h"
#include "mruby/object.h"
#include "mruby/value.h"
#include "mruby/variable.h"
#include "mruby/array.h"

#include "unbound.h"

#include <arpa/inet.h>


static mrb_value mrb_unbound_result_qname(mrb_state *mrb, mrb_value self)
{
    return mrb_obj_iv_get(mrb, mrb_ptr(self), mrb_intern_cstr(mrb, "_qname"));
}
static mrb_value mrb_unbound_result_qtype(mrb_state *mrb, mrb_value self)
{
    return mrb_obj_iv_get(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_qtype"));
}

static mrb_value mrb_unbound_result_qclass(mrb_state *mrb, mrb_value self)
{
    return mrb_obj_iv_get(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_qclass"));;
}
static mrb_value mrb_unbound_result_data(mrb_state *mrb, mrb_value self)
{
    return mrb_obj_iv_get(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_data"));
}
static mrb_value mrb_unbound_result_canonname(mrb_state *mrb, mrb_value self)
{
    return mrb_obj_iv_get(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_canonname"));
}
static mrb_value mrb_unbound_result_rcode(mrb_state *mrb, mrb_value self)
{
    return mrb_obj_iv_get(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_rcode"));
}
static mrb_value mrb_unbound_result_answer(mrb_state *mrb, mrb_value self)
{
    return mrb_obj_iv_get(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_answer"));
}
static mrb_value mrb_unbound_result_nxdomain(mrb_state *mrb, mrb_value self)
{
    return mrb_obj_iv_get(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_nxdomain"));
}
static mrb_value mrb_unbound_result_secure(mrb_state *mrb, mrb_value self)
{
    return mrb_obj_iv_get(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_secure"));
}
static mrb_value mrb_unbound_result_bogus(mrb_state *mrb, mrb_value self)
{
    return mrb_obj_iv_get(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_bogus"));
}
static mrb_value mrb_unbound_result_why_bogus(mrb_state *mrb, mrb_value self)
{
    return mrb_obj_iv_get(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_why_bogus"));
}
static mrb_value mrb_unbound_result_ttl(mrb_state *mrb, mrb_value self)
{
    return mrb_obj_iv_get(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_ttl"));
}

static mrb_value mrb_unbound_result_initialize(mrb_state *mrb, mrb_value self)
{

    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_qname"),        mrb_str_new_cstr(mrb,""));
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_why_bogus"),   mrb_str_new_cstr(mrb, ""));
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_answer"),       mrb_str_new_cstr(mrb, ""));
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_cannonname"),   mrb_str_new_cstr(mrb, ""));

    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_qtype"),        mrb_fixnum_value(0) );
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_qclass"),       mrb_fixnum_value(0) );
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_rcode"),        mrb_fixnum_value(0) );
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_ttl"),          mrb_fixnum_value(0));

    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_nxdomain"),     mrb_false_value());
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_secure"),       mrb_false_value());
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_bogus"),        mrb_false_value());

    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_data"),         mrb_ary_new(mrb) );

    return self;
}

void mrb_define_unbound_result(mrb_state *mrb) 
{
    struct RClass *result, *unbound;

    unbound = mrb_class_get(mrb, "Unbound");

    result = mrb_define_class_under(mrb, unbound, "Result", mrb->object_class);

    mrb_define_method(mrb, result, "initialize", mrb_unbound_result_initialize, MRB_ARGS_REQ(1) );

    mrb_define_method(mrb, result, "qname", mrb_unbound_result_qname, MRB_ARGS_NONE());
    mrb_define_method(mrb, result, "qtype", mrb_unbound_result_qtype, MRB_ARGS_NONE());
    mrb_define_method(mrb, result, "qclass", mrb_unbound_result_qclass, MRB_ARGS_NONE());
    mrb_define_method(mrb, result, "data", mrb_unbound_result_data, MRB_ARGS_NONE());
    mrb_define_method(mrb, result, "canonname", mrb_unbound_result_canonname, MRB_ARGS_NONE());
    mrb_define_method(mrb, result, "rcode", mrb_unbound_result_rcode, MRB_ARGS_NONE());
    mrb_define_method(mrb, result, "answer", mrb_unbound_result_rcode, MRB_ARGS_NONE());
    mrb_define_method(mrb, result, "nxdomain", mrb_unbound_result_nxdomain, MRB_ARGS_NONE());
    mrb_define_method(mrb, result, "secure", mrb_unbound_result_secure, MRB_ARGS_NONE());
    mrb_define_method(mrb, result, "bogus", mrb_unbound_result_bogus, MRB_ARGS_NONE());
    mrb_define_method(mrb, result, "ttl", mrb_unbound_result_ttl, MRB_ARGS_NONE());
}

mrb_value mrb_result_iv_set(mrb_state *mrb, mrb_value self, struct ub_result *result) 
{
    int i = 0;
    char **p;
    mrb_value data;

    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_qname"),        mrb_str_new_cstr(mrb,result->qname));
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_why_bogus"),   mrb_str_new_cstr(mrb, result->why_bogus));
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb ,"_canonname"),   mrb_str_new_cstr(mrb, result->canonname));
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_answer"),       mrb_str_new(mrb, result->answer_packet, result->answer_len * sizeof(char)));

    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_qtype"),        mrb_fixnum_value(result->qtype) );
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_qclass"),       mrb_fixnum_value(result->qclass) );
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_rcode"),        mrb_fixnum_value(result->rcode) );
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_ttl"),          mrb_fixnum_value(result->ttl));

    if(result->nxdomain)
    {
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_nxdomain"),     mrb_true_value());
    }
    if(result->secure)
    {
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_secure"),       mrb_true_value());
    }
    if(result->bogus)
    {
    mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_bogus"),        mrb_true_value());
    }


    if(result->havedata)
    {
        data = mrb_ary_new(mrb);
        for(p = result->data; *p != NULL; p++)
        {
            mrb_ary_push(mrb, data, mrb_str_new_cstr(mrb, inet_ntoa( *(struct in_addr*)*p)) );
        }
        mrb_obj_iv_set(mrb, mrb_obj_ptr(self), mrb_intern_cstr(mrb, "_data"),         data);
    }


    return self;
}
