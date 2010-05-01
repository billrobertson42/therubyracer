
module V8
  class Object
    include Enumerable
    
    def initialize(native)
      @native = native
    end
    
    def [](key)
      puts "Object::[#{key}] #{@native}"      
      @native.context.enter
      foo = To.ruby(@native.Get(key.to_s))
      @native.context.exit
      puts foo
      return foo
    end
    
    def []=(key, value)
      @native.context.enter        
      @native.Set(key.to_s, value)
      @native.context.exit        
    end
    
    def to_s
      @native.context.enter
      @native.ToString()
      @native.context.exit        
    end
    
    def each
      @native.context.enter
      for prop in @native.GetPropertyNames()
        yield prop, self[prop]
      end
      @native.context.exit        
    end
  end
end

class Object  
  def eval_js(javascript)
    V8::Context.open(:with => self) do |cxt|
      cxt.eval(javascript)
    end
  end
end