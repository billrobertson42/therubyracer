require 'stringio'

module V8  
  class Context    
    def initialize(opts = {})
      puts "initialize"
      @native = C::Context.new(opts[:with])
    end
    
    def open(&block)
      if block_given?
        unless @native == C::Context::GetCurrent()
          @native.open do
            block.call(self)
          end
        else
          block.call(self)
        end
      end
    end
    
    def entered?
      @native.is_entered
    end
    
    def eval(javascript, sourcename = '<eval>', line = 1)
      puts "eval"
      if IO === javascript || StringIO === javascript
        javascript = javascript.read()
      end
      puts "enter"
      @native.enter
      puts "eval"
      result = @native.eval(javascript, sourcename)
      puts "exit"
      @native.exit
      raise JavascriptError.new(result) if result.kind_of?(C::Message)
      return To.ruby(result)
    end
        
    def evaluate(*args)
      self.eval(*args)
    end
    
    def load(filename)
      File.open(filename) do |file|
        evaluate file, filename, 1
      end      
    end
    
    def [](key)
      puts "def []=(#{key})"
      @native.enter
      result = @native.get key
      @native.exit
      Object.new result
    end
    
    def []=(key, value)
      puts "def []=(#{key}, #{value})"
      @native.enter
      @native.set key, value
      @native.exit
    end
    
    def self.open(opts = {}, &block)
      new(opts).open(&block)
    end
    
    def self.eval(source)
      puts "self.eval"
      new.eval(source)
    end
    
    def V8.eval(*args)
      puts "V8.eval"
      V8::Context.eval(*args)
    end
  end
  
  class ContextError < StandardError
    def initialize(caller_name)
      super("tried to call method '#{caller_name} without an open context")
    end
    def self.check_open(caller_name)
      raise new(caller_name) unless C::Context::InContext()
    end
  end
  class JavascriptError < StandardError
    def initialize(v8_message)
#      super("#{v8_message.Get()}: #{v8_message.GetScriptResourceName()}:#{v8_message.GetLineNumber()}")
      super("foo")
      @native = v8_message
    end

    def source_name
      @native.GetScriptResourceName()      
    end
    
    def source_line
      @native.GetSourceLine()
    end
    
    def line_number
      @native.GetLineNumber()
    end
    
    def javascript_stacktrace
      @native.stack
    end
    
  end
  class RunawayScriptError < ContextError
  end
  
  module C
    class Message
      attr_reader :stack
    end
  end
end
