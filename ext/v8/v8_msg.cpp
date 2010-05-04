#include "converters.h"
#include "v8_msg.h"
#include "v8_ref.h"

using namespace v8;
using namespace std;

VALUE V8_C_Message;

namespace {
  
  /**
   * A class to hold the v8 exception information that we can access
   * outside of a context.  That way we don't have to fiddle with contexts
   * when things go wrong.
   */
  class RRMessage {
  private:
    string script;
    string msg;
    string sourceLine;
    int lineNumber;
    int startPos;
    int endPos;
    int startCol;
    int endCol;
  
  public:
    RRMessage(Handle<Message>& message) :
      startPos(message->GetStartPosition()),
      endPos(message->GetEndPosition()),
      startCol(message->GetStartColumn()),
      endCol(message->GetEndColumn()) {
        Handle<Value> scriptResourceNameHandle = message->GetScriptResourceName();
        Handle<Value> messageHandle = message->Get();
        Handle<Value> sourceLineHandle = message->GetSourceLine();  
        script = V82String(scriptResourceNameHandle);
        msg = V82String(messageHandle);
        sourceLine = V82String(sourceLineHandle);
        lineNumber = message->GetLineNumber();
        printf("LineNumber (a) %d\n", lineNumber);        
    }

    const char* GetScriptResourceName() {
      return script.c_str();
    }
        
    const char* GetMessage() {
      return msg.c_str();
    }
    
    const char* GetSourceLine() {
      return sourceLine.c_str();
    }
    
    int GetLineNumber() {
      return lineNumber;
    }
    
    int GetStartPos() { 
      return startPos;
    }
    
    int GetEndPos() {
      return endPos;
    }
    
    int GetStartCol() {
      return startPos;
    }
    
    int GetEndCol() {
      return endPos;
    }
    
};
  
  RRMessage* unwrap(VALUE wrapper) {
    RRMessage* mess = 0;
    Data_Get_Struct(wrapper, class RRMessage, mess);
    return mess;
  }
}

extern "C" {
  void mark_mess(RRMessage* ref) {
  }

  void free_mess(RRMessage* ref) {
    delete ref;
  }
}

VALUE v8_wrap_message(Handle<v8::Message> msg) {
  printf("v8_wrap_message");
  RRMessage* mess = new RRMessage(msg);
  return Data_Wrap_Struct(V8_C_Message, mark_mess, free_mess, mess);
}

VALUE v8_message_get(VALUE self) {
  RRMessage* mess = unwrap(self);
  return rb_str_new2(mess->GetMessage());
}

VALUE v8_message_get_source_line(VALUE self) {
  RRMessage* mess = unwrap(self);
  return rb_str_new2(mess->GetSourceLine());
}

VALUE v8_message_get_script_resource_name(VALUE self) {
  RRMessage* mess = unwrap(self);
  return rb_str_new2(mess->GetScriptResourceName());
}

VALUE v8_message_get_line_number(VALUE self) {
  RRMessage* mess = unwrap(self);
  printf("Line Number (b) %d\n", mess->GetLineNumber());
  return INT2FIX(mess->GetLineNumber());
}

VALUE v8_message_get_start_position(VALUE self) {
  RRMessage* mess = unwrap(self);
  return INT2FIX(mess->GetStartPos());
}

VALUE v8_message_get_end_position(VALUE self) {
  RRMessage* mess = unwrap(self);
  return INT2FIX(mess->GetEndPos());
}

VALUE v8_message_get_start_column(VALUE self) {
  RRMessage* mess = unwrap(self);
  return INT2FIX(mess->GetStartCol());
}

VALUE v8_message_get_end_column(VALUE self) {
  RRMessage* mess = unwrap(self);
  return INT2FIX(mess->GetEndCol());
}
