#include "v8_cxt.h"
#include "v8_str.h"
#include "v8_obj.h"
#include "v8_msg.h"
#include "v8_func.h"
#include "v8_script.h"
#include "v8_template.h"
#include "v8_standalone.h"
#include "converters.h"

#include <stdio.h>

extern "C" {
    /**
     * ruby init method for the extension
     */
    void Init_v8();
}

VALUE rb_mModule;
VALUE rb_cV8;

extern "C" {
    void Init_v8() {
      
        ruby_call_symbol = ID2SYM(rb_intern("call"));
        ruby_respond_to_ID = rb_intern("respond_to?");
        ruby_proc_class = rb_eval_string("::Proc");
        ruby_method_class = rb_eval_string("::Method");
      
        rb_mModule = rb_define_module("V8");
        rb_define_singleton_method(rb_mModule, "what_is_this?", (VALUE(*)(...)) v8_what_is_this, 1);
        
        V8_To = rb_define_module_under(rb_mModule, "To");
                
        //native module setup
        VALUE rb_mNative = rb_define_module_under(rb_mModule, "C");
        
        //native context
        V8_C_Context = rb_define_class_under(rb_mNative, "Context", rb_cObject);
        rb_define_singleton_method(V8_C_Context, "new", (VALUE(*)(...)) v8_cxt_new, -1);
        rb_define_method(V8_C_Context, "eql?", (VALUE(*)(...)) v8_cxt_eql, 1);
        rb_define_method(V8_C_Context, "==", (VALUE(*)(...)) v8_cxt_eql, 1);
        rb_define_method(V8_C_Context, "get", (VALUE(*)(...)) v8_cxt_get_global_val, 1);
        rb_define_method(V8_C_Context, "set", (VALUE(*)(...)) v8_cxt_set_global_val, 2);

        rb_define_method(V8_C_Context, "enter", (VALUE(*)(...)) v8_cxt_enter, 0);
        rb_define_method(V8_C_Context, "eval", (VALUE(*)(...)) v8_cxt_eval, 2);
        rb_define_method(V8_C_Context, "exit",  (VALUE(*)(...)) v8_cxt_exit, 0);
        rb_define_method(V8_C_Context, "is_entered", (VALUE(*)(...)) v8_cxt_is_entered, 0);
        
        //native String
        VALUE V8__C__String = rb_define_class_under(rb_mNative, "String", rb_cObject);
        rb_define_singleton_method(V8__C__String, "new", (VALUE(*)(...)) v8_str_new, 1);
        rb_define_method(V8__C__String, "to_s", (VALUE(*)(...)) v8_str_to_s, 0);
        
        VALUE V8__C__Script = rb_define_class_under(rb_mNative, "Script", rb_cObject);
        rb_define_singleton_method(V8__C__Script, "new", (VALUE(*)(...)) v8_script_new, 1);
        rb_define_method(V8__C__Script, "Run", (VALUE(*)(...)) v8_script_Run, 0);
        
        VALUE V8__C__Template = rb_define_class_under(rb_mNative, "Template", rb_cObject);
        rb_define_method(V8__C__Template, "Set", (VALUE(*)(...))v8_Template_Set, 2);
        
        VALUE V8__C__ObjectTemplate = rb_define_class_under(rb_mNative, "ObjectTemplate", V8__C__Template);
        rb_define_singleton_method(V8__C__ObjectTemplate, "new", (VALUE(*)(...))v8_ObjectTemplate_New, 0);
        
        VALUE V8__C__FunctionTemplate = rb_define_class_under(rb_mNative, "FunctionTemplate", V8__C__Template);
        rb_define_singleton_method(V8__C__FunctionTemplate, "new", (VALUE(*)(...))v8_FunctionTemplate_New, -1);
        rb_define_method(V8__C__FunctionTemplate, "GetFunction", (VALUE(*)(...))v8_FunctionTemplate_GetFunction, 0);
        
        V8_C_Object = rb_define_class_under(rb_mNative, "Object", rb_cObject);
        rb_define_singleton_method(V8_C_Object, "new", (VALUE(*)(...))v8_object_new, 0);
        rb_define_method(V8_C_Object, "Get", (VALUE(*)(...))v8_object_get, 1);
        rb_define_method(V8_C_Object, "Set", (VALUE(*)(...))v8_object_set, 2);
        rb_define_method(V8_C_Object, "GetPropertyNames", (VALUE(*)(...)) v8_object_get_property_names, 0);
        rb_define_method(V8_C_Object, "ToString", (VALUE(*)(...)) v8_object_to_string, 0);
        rb_define_method(V8_C_Object, "context", (VALUE(*)(...)) v8_object_context, 0);

        V8_C_Message = rb_define_class_under(rb_mNative, "Message", rb_cObject);
        rb_define_method(V8_C_Message, "Get", (VALUE(*)(...))v8_message_get, 0);
        rb_define_method(V8_C_Message, "GetSourceLine", (VALUE(*)(...))v8_message_get_source_line, 0);
        rb_define_method(V8_C_Message, "GetScriptResourceName", (VALUE(*)(...))v8_message_get_script_resource_name, 0);
        rb_define_method(V8_C_Message, "GetLineNumber", (VALUE(*)(...))v8_message_get_line_number, 0);
        rb_define_method(V8_C_Message, "GetStartPosition", (VALUE(*)(...))v8_message_get_start_position, 0);
        rb_define_method(V8_C_Message, "GetEndPosition", (VALUE(*)(...)) v8_message_get_end_position, 0);
        rb_define_method(V8_C_Message, "GetStartColumn", (VALUE(*)(...)) v8_message_get_start_column, 0);
        rb_define_method(V8_C_Message, "GetEndColumn", (VALUE(*)(...)) v8_message_get_end_column, 0);
        
        V8_C_Function = rb_define_class_under(rb_mNative, "Function", V8_C_Object);
    }
}
