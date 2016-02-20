
/* mrb_unbound.c - Unbound Class
 *
 *
 */

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/string.h"
#include "mruby/class.h"
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

static void mrb_unbound_data_free(mrb_state *mrb, void *p)
{
    mrb_unbound_data *data = (mrb_unbound_data *)p;
    ub_ctx_delete(data->ctx);
}

static const struct mrb_data_type mrb_unbound_data_type = {
    "mrb_unbound_data", mrb_unbound_data_free
};

static mrb_value mrb_unbound_init(mrb_state *mrb, mrb_value self)
{
    struct ub_ctx *ctx;

    mrb_unbound_data *data = (mrb_unbound_data *)DATA_PTR(self);
    if(data)
    {
        mrb_free(mrb, data);
    }
    mrb_data_init(self, NULL, &mrb_unbound_data_type);
    data = (mrb_unbound_data *)mrb_malloc(mrb, sizeof(mrb_unbound_data) );

    ctx  = ub_ctx_create();
    if(!ctx)
    {
        mrb_raisef(mrb, E_RUNTIME_ERROR, "libunbound error: %S", mrb_str_new_cstr(mrb, "could not create unbound context\n") );
    }

    data->ctx = ctx;

    mrb_data_init(self, data, &mrb_unbound_data_type);
    return self;
}

// power user option. low priority
static mrb_value mrb_ub_set_option(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    struct ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    mrb_value opt;
    int i;
    char *op,*v;

    mrb_get_args(mrb,"Sz",&opt, &v);
    op = mrb_str_to_cstr(mrb, opt);
    i = ub_ctx_set_option(ctx, op, v);

    return mrb_str_new(mrb,v,sizeof(v));
}

//power user potion. low priority
static mrb_value mrb_ub_get_option(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    struct ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    mrb_value val;
    char *opt, *v;
    int i;
    mrb_get_args(mrb,"S",&val);
    opt = mrb_str_to_cstr(mrb,val);

    i = ub_ctx_get_option(ctx,opt,&v);

    return mrb_str_new(mrb,v,sizeof(v));;
}

// power user option. low priority
static mrb_value mrb_ub_ctx_config(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    struct ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    mrb_value fname;
    int i;
    char *f;
    ctx = data->ctx;

    mrb_get_args(mrb,"S",&fname);

    f = mrb_str_to_cstr(mrb, fname); 
    i= ub_ctx_config(ctx, f);

    
    return mrb_fixnum_value(i);
}

// fowrder setting
static mrb_value mrb_ub_ctx_set_fwd(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data=(mrb_unbound_data *)DATA_PTR(self);
    struct ub_ctx *ctx;
    int i;
    char *p;
    mrb_value arg;
    ctx = data->ctx;

    mrb_get_args(mrb,"S",&arg);
    p = mrb_str_to_cstr(mrb,arg);

    i = ub_ctx_set_fwd(ctx, p);
    return mrb_fixnum_value(i);
}

//config
static mrb_value mrb_ub_ctx_resolvconf(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    data = (mrb_unbound_data *)DATA_PTR(self);
    struct ub_ctx *ctx = data->ctx;
    mrb_value fname;
    mrb_int i;
    char *f =NULL;

    mrb_get_args(mrb,"S",&fname);
    f = mrb_str_to_cstr(mrb,fname);

    i = ub_ctx_resolvconf(ctx, f);
    return mrb_fixnum_value(i);
}

static mrb_value mrb_ub_ctx_hosts(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data = (mrb_unbound_data *)DATA_PTR(self);
    struct ub_ctx *ctx = data->ctx;
    mrb_value fname;
    char *f=NULL;
    mrb_int i;

    mrb_get_args(mrb,"S",&fname);
    f = mrb_str_to_cstr(mrb, fname);

    i = ub_ctx_hosts(ctx,f);

    return mrb_fixnum_value(i);
}


static mrb_value mrb_ub_ctx_add_ta(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data = (mrb_unbound_data *)DATA_PTR(self);
    struct ub_ctx *ctx = data->ctx;
    mrb_value s;
    mrb_int i;
    char *p;

    mrb_get_args(mrb,"S",&s);
    p = mrb_str_to_cstr(mrb, s);

    i = ub_ctx_add_ta(ctx, p);

    return mrb_fixnum_value(i);
}

static mrb_value mrb_ub_ctx_add_ta_autr(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data = (mrb_unbound_data *)DATA_PTR(self);
    struct ub_ctx *ctx = data->ctx;
    mrb_value v;
    char *p;
    mrb_int i;

    mrb_get_args(mrb,"S", &v);
    p = mrb_str_to_cstr(mrb,v);

    i = ub_ctx_add_ta_autr(ctx ,p);
    return mrb_fixnum_value(i);
}

static mrb_value mrb_ub_ctx_add_ta_file(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data = (mrb_unbound_data *)DATA_PTR(self);
    struct ub_ctx *ctx = data->ctx;
    mrb_value v;
    char *p=NULL;
    mrb_int i;

    mrb_get_args(mrb,"S", &v);
    p = mrb_str_to_cstr(mrb,v);

    i = ub_ctx_add_ta_file(ctx, p);
    return mrb_fixnum_value(i);
}

// low priorty
static mrb_value mrb_ub_ctx_trustedkeys(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    struct ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);
    ctx = data->ctx;
    mrb_value fname;
    char *f=NULL;
    int i=0;

    mrb_get_args(mrb,"S",&fname);
    f = mrb_str_to_cstr(mrb,fname);

    i = ub_ctx_trustedkeys(ctx,f);
    return mrb_true_value();
}
/*
 * it maybe needs mruby-file
static mrb_value mrb_ub_ctx_debugout(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data;
    struct ub_ctx *ctx;
    data = (mrb_unbound_data *)DATA_PTR(self);

    ctx = data->ctx;
    return mrb_nil_value();
}
*/

// developer api
static mrb_value mrb_ub_ctx_debuglevel(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data = (mrb_unbound_data *)DATA_PTR(self);
    struct ub_ctx *ctx = data->ctx;
    mrb_int level, res;

    mrb_get_args(mrb,"i", &level);

    res = ub_ctx_debuglevel(ctx,level);
    return mrb_fixnum_value(res);
}

/*
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
    mrb_unbound_data *data = (mrb_unbound_data *)DATA_PTR(self);
    struct ub_ctx *ctx = data->ctx;
    mrb_int poll;


    poll = ub_poll(ctx);
    return mrb_fixnum_value(poll);
}

// absolutely need
static mrb_value mrb_ub_fd(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data= (mrb_unbound_data *)DATA_PTR(self);
    mrb_int fd;

    fd = ub_fd(data->ctx);
    return mrb_fixnum_value(fd);
}

// absolutely need
static mrb_value mrb_ub_process(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data =(mrb_unbound_data *)DATA_PTR(self);
    struct ub_ctx *ctx =data->ctx;
    mrb_int num;

    num = ub_process(ctx);
    
    return mrb_fixnum_value(num);
}


// absolutely need
static mrb_value mrb_ub_resolve(mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data = (mrb_unbound_data *)DATA_PTR(self);
    struct ub_ctx *ctx = data->ctx;
    struct ub_result *result;
    struct in_addr *addr;
    int retval;
    mrb_int  rrtype=1, rrclass=1;
    mrb_value val,qname;
    char *name;

    mrb_get_args(mrb,"S|ii",&qname,&rrtype,&rrclass);
    name= mrb_str_to_cstr(mrb, qname);
    

    retval = ub_resolve(ctx, name, rrtype, rrclass, &result);
    if(retval != 0 || !result->havedata)
    {
        return mrb_nil_value();
    }

    addr = (struct in_addr*)result->data[0];
    return mrb_str_new_cstr(mrb, inet_ntoa(*addr));
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

    mrb_get_args(mrb,"Si",&str,&rrtype);

    ub_resolve_async(ctx, str, rrtype, 1, MYDATA, , NULL);


    
    return mrb_str_new_cstr("");
}
*/

static mrb_value mrb_ub_cancel (mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data = (mrb_unbound_data*)DATA_PTR(self);
    struct ub_ctx *ctx = data->ctx;
    mrb_int i, number=0;
    mrb_get_args(mrb,"i",&number);

    i =ub_cancel(ctx,number);
    return mrb_fixnum_value(i);
}

//low priority
static mrb_value mrb_ub_ctx_print_local_zones (mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data = (mrb_unbound_data*)DATA_PTR(self);
    struct ub_ctx *ctx = data->ctx;
    mrb_int i;

    i = ub_ctx_print_local_zones(ctx);
    return mrb_fixnum_value(i);
}

//low priority
static mrb_value mrb_ub_ctx_zone_add (mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data  = (mrb_unbound_data*)DATA_PTR(self);
    struct ub_ctx *ctx = data->ctx;
    mrb_value type, zname;
    char *z,*t;
    mrb_int i;
    mrb_get_args(mrb,"SS",&zname,&type);
    z = mrb_str_to_cstr(mrb,zname);
    t = mrb_str_to_cstr(mrb, type);
    

    i= ub_ctx_zone_add(ctx, z, t);

    return mrb_fixnum_value(i);
}

static mrb_value mrb_ub_ctx_zone_remove (mrb_state *mrb, mrb_value self)
{
    mrb_unbound_data *data  = (mrb_unbound_data*)DATA_PTR(self);
    struct ub_ctx *ctx = data->ctx;
    mrb_value d;
    mrb_int i;
    char *p;

    mrb_get_args(mrb,"S",&d);
    p = mrb_str_to_cstr(mrb, d);
    i = ub_ctx_zone_remove(ctx, p);
    return mrb_fixnum_value(i);
}


void mrb_mruby_unbound_gem_init(mrb_state *mrb)
{
    struct RClass *unbound ;
    unbound = mrb_define_class(mrb, "Unbound",  mrb->object_class);
    MRB_SET_INSTANCE_TT(unbound, MRB_TT_DATA);

    mrb_define_method(mrb,  unbound,    "initialize",   mrb_unbound_init,       MRB_ARGS_NONE()     );
    mrb_define_method(mrb,  unbound,    "resolve",      mrb_ub_resolve,         MRB_ARGS_ARG(1,2)   );
    mrb_define_method(mrb,  unbound,    "resolvconf",   mrb_ub_ctx_resolvconf,  MRB_ARGS_REQ(1)     );
    mrb_define_method(mrb,  unbound,    "set_option",   mrb_ub_set_option,      MRB_ARGS_REQ(1)     );
    mrb_define_method(mrb,  unbound,    "get_option",   mrb_ub_get_option,      MRB_ARGS_REQ(1)     );
    mrb_define_method(mrb,  unbound,    "hosts",        mrb_ub_ctx_hosts,       MRB_ARGS_REQ(1)     );
    mrb_define_method(mrb,  unbound,    "config",       mrb_ub_ctx_config,      MRB_ARGS_REQ(1)     );
    mrb_define_method(mrb,  unbound,    "set_fwd",      mrb_ub_ctx_set_fwd,     MRB_ARGS_REQ(1)     );
    mrb_define_method(mrb,  unbound,    "add_ta",       mrb_ub_ctx_add_ta,      MRB_ARGS_REQ(1)     );
    mrb_define_method(mrb,  unbound,    "add_ta_autr",  mrb_ub_ctx_add_ta_autr, MRB_ARGS_REQ(1)     );
    mrb_define_method(mrb,  unbound,    "add_ta_file",  mrb_ub_ctx_add_ta_file, MRB_ARGS_REQ(1)     );
    mrb_define_method(mrb,  unbound,    "trustedkeys",  mrb_ub_ctx_trustedkeys, MRB_ARGS_REQ(1)     );
    mrb_define_method(mrb,  unbound,    "debuglevel",   mrb_ub_ctx_debuglevel,  MRB_ARGS_REQ(1)     );
    mrb_define_method(mrb,  unbound,    "fd",           mrb_ub_fd,              MRB_ARGS_NONE()     );
    mrb_define_method(mrb,  unbound,    "poll",         mrb_ub_poll,            MRB_ARGS_NONE()     );
    mrb_define_method(mrb,  unbound,    "process",      mrb_ub_process,         MRB_ARGS_NONE()     );
    mrb_define_method(mrb,  unbound,    "cancel",       mrb_ub_cancel,         MRB_ARGS_REQ(1)     );
    mrb_define_method(mrb,  unbound,    "print_local_zones",      mrb_ub_ctx_print_local_zones,         MRB_ARGS_NONE()     );
    mrb_define_method(mrb,  unbound,    "zone_add",       mrb_ub_ctx_zone_add,         MRB_ARGS_REQ(2)     );
    mrb_define_method(mrb,  unbound,    "zone_remove",       mrb_ub_ctx_zone_remove,         MRB_ARGS_REQ(1)     );
/*  
 *  mrb_define_method(mrb,  unbound,    "async",        mrb_ub_ctx_async,       MRB_ARGS_ARG(1,3)   );
    */
}

void mrb_mruby_unbound_gem_final(mrb_state *mrb)
{
}


