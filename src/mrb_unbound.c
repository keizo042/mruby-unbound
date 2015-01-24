
/* mrb_unbound.c - Unbound Class
 *
 *
 */

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/string.h"
#include "mruby/value.h"
#include "mrb_unbound.h"
#include <unbound.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define ADDR_LEN 37
typedef struct {
    struct ub_ctx *ctx;
}mrb_unbound_data;

static void mrb_unbound_data_free(mrb_state *mrb, void *p);
    
static const mrb_data_type mrb_unbound_data_type = {
    "mrb_unbound_data", mrb_unbound_data_free
};

static void mrb_unbound_data_free(mrb_state *mrb, void *p)
{
    mrb_unbound_data *data = (mrb_unbound_data *)p;
    ub_ctx_delete(data->ctx);
    mrb_free(mrb, data);
}

static mrb_value mrb_unbound_init(mrb_state *mrb, mrb_value self)
{
    mrb_int port=53;
    mrb_unbound_data *data = (mrb_unbound_data *)DATA_PTR(self);
    struct ub_ctx *ctx;

    mrb_get_args(mrb,"|i",&port);

    mrb_data_init(self, NULL, &mrb_unbound_data_type);

    data =(mrb_unbound_data *)mrb_malloc(mrb, sizeof(mrb_unbound_data) );
    ctx  = ub_ctx_create();
    if(!ctx)
    {
        mrb_free(mrb, data);
        mrb_raisef(mrb, E_RUNTIME_ERROR, "libunbound error: %S", mrb_str_new_cstr(mrb, "could not create unbound context\n") );
    }
    if(data){
        mrb_free(mrb, data);
    }
    data->ctx = ctx;

    mrb_data_init(self, data, &mrb_unbound_data_type);
    return self;
}

/*
// power user option. low priority
static mrb_value mrb_ub_ctx_set_option(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    ub_ctx *data;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;

    return self;
}

//power user potion. low priority
static mrb_ub_get_option(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;

    return self;
}

// power user option. low priority
static mrb_value mrb_ub_ctx_config(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    return self;
}

// fowrder setting
static mrb_value mrb_ub_ctx_set_fwd(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    return mrb_false_value();
}

//config
static mrb_value mrb_ub_ctx_resolvconf(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    return mrb_fixnum_value(0);
}

static mrb_value mrb_ub_ctx_hosts(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    return mrb_fixnum_value(0);
}


static mrb_value mrb_ub_ctx_add_ta(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;

    return mrb_fixnum_value(0);
}

static mrb_value mrb_ub_ctx_add_ta_autr(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    return mrb_fixnum_value(0);
}

static mrb_value mrb_ub_ctx_add_ta_file(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    return mrb_nil_value;
}

// low priorty
static  mrb_valuemrb_ub_ctx_trustedkeys(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    return mrb_nil_value();
}
//low priority
static mrb_value mrb_ub_ctx_debugout(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    return mrb_nil_value();
}

// developer api
static mrb_value mrb_ub_ctx_debuglevel(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    return mrb_nil_value();
}

// absolutely need
static mrb_value mrb_ub_ctx_async(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    return mrb_fixnum_value(0);
}
*/

// absolutely need
static mrb_value mrb_ub_poll(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    struct ub_ctx *ctx;
    mrb_int poll;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    poll = ub_poll(ctx);
    return mrb_fixnum_value(poll);
}

// absolutely need
static mrb_value mrb_ub_fd(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data= (mrb_unbound_data *)DATA_PTR(self);
    mrb_int fd;
    if(data->ctx == NULL)
    {
        return mrb_nil_value();
    }

    fd = ub_fd(data->ctx);
    return mrb_fixnum_value(fd);
}

// absolutely need
static mrb_value mrb_ub_process(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    struct ub_ctx *ctx;
    mrb_int num;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    if(ctx == NULL)
    {
        return mrb_nil_value();
    }
    num = ub_process(ctx);
    
    return mrb_fixnum_value(num);
}


// absolutely need
static mrb_value mrb_ub_resolve(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    struct ub_ctx *ctx;
    int retval;
    struct ub_result *result;
    struct in_addr addr;
    mrb_int  rrtype=1, rrclass=1;
    mrb_value val,qname;
    char name[ADDR_LEN];

    mrb_get_args(mrb,"S|ii",qname,&rrtype,&rrclass);

    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    if(ctx == NULL)
    {
        return mrb_nil_value();
    }

    retval = ub_resolve(ctx, mrb_str_to_cstr(mrb,qname), (int)rrtype, (int)rrclass, &result);
    
    if(retval != 0)
    {
        return mrb_nil_value();
    }

    if(!result->havedata)
    {
        return mrb_nil_value();
    }

    addr = *(struct in_addr*)result->data[0];

    strncpy( name, inet_ntoa(addr), ADDR_LEN);

    return mrb_str_new(mrb, name, ADDR_LEN);
}
/*

// absolutely need
static mrb_value mrb_resolv_async (mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    struct ub_ctx *ctx;
    struct ub_result *result;
    //void *call_back(void *mydata, int err, struct ub_ctx* result);

    int retval;
    mrb_int rrtype;
    mrb_value str;

    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;

    mrb_get_args(mrb,"Si",str,&rrtype);

    ub_resolve_async(ctx, str, rrtype, 1, MYDATA, , NULL);


    
    return mrb_str_new_cstr("");
}

static mrb_value mrb_ub_cancel (mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    struct ub_ctx *ctx;
    struct ub_result *result;

    ub_cancel(ctx,NULL);
    return mrb_nil_value();
}

//low priority
static mrb_value mrb_ub_ctx_print_local_zones (mrb_state *mrb, mrb_value self)
{

    return mrb_nil_value();
}

//low priority
static mrb_value mrb_ub_ctx_zone_add (mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    struct ub_ctx *ctx;
    struct ub_result *result;
    int retval;
    data = DATA_PTR(data);
    ctx = data->ctx;

    return mrb_fixnum_value(0);
}

static mrb_value mrb_ctx_zone_remove (mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(0);
}
*/


void mrb_mruby_unbound_gem_init(mrb_state *mrb)
{
    struct RClass *unbound = mrb_define_class(mrb,  "Unbound",  mrb->object_class);

    mrb_define_method(mrb,  unbound,    "initialize",    mrb_unbound_init,       MRB_ARGS_OPT(1)     );
    mrb_define_method(mrb,  unbound,    "resolve",      mrb_ub_resolve,         MRB_ARGS_ARG(1,2)   );
    mrb_define_method(mrb,  unbound,    "fd",           mrb_ub_fd,              MRB_ARGS_NONE()     );
    mrb_define_method(mrb,  unbound,    "process",      mrb_ub_process,         MRB_ARGS_NONE()     );
    mrb_define_method(mrb,  unbound,    "poll",         mrb_ub_poll,            MRB_ARGS_NONE()     );
/*  mrb_define_method(mrb,  unbound,    "async",        mrb_ub_ctx_async,       MRB_ARGS_ARG(1,3)   );
    mrb_define_method(mrb,  unbound,    "resolvconf",   mrb_ub_ctx_resolvconf,  MRB_ARGS_REQ(1)     );
    mrb_define_method(mrb,  unbound,    "hosts",        mrb_ub_ctx_hosts,       MRB_ARGS_REQ(1)     );
    */
}

void mrb_mruby_unbound_gem_final(mrb_state *mrb)
{
}


