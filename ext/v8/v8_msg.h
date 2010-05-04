#ifndef _RUBY_V8_MESSAGE_
#define _RUBY_V8_MESSAGE_ 

#include "v8.h"
#include "ruby.h"

extern VALUE V8_C_Message;

VALUE v8_wrap_message(v8::Handle<v8::Message> msg);
VALUE v8_message_get(VALUE self);
VALUE v8_message_get_source_line(VALUE self);
VALUE v8_message_get_script_resource_name(VALUE self);
VALUE v8_message_get_line_number(VALUE self);
VALUE v8_message_get_start_position(VALUE self);
VALUE v8_message_get_end_position(VALUE self);
VALUE v8_message_get_start_column(VALUE self);
VALUE v8_message_get_end_column(VALUE self);

#endif