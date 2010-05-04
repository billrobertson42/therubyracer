require File.dirname(__FILE__) + '/../spec_helper'

include V8

describe "A Javascript Object Reflected Into Ruby" do

  it "should not have a current context if no context is open" do
    cxt = Context.new
    rputs cxt.eval('"Hi There"', "<eval>")
    cxt2 = Context.new
    rputs cxt2.eval('7 * 6', "<eval>")
    C::Context::GetCurrent().should be_nil  
  end
  
=begin  
  specify "inline madness" do
    cxt = Context.new
    cxt.open do |cxt|
      cxt.eval('1')
    end
        
    C::Context::GetCurrent().should be_nil
  end
  
  specify "more madness" do
    cxt = Context.new
    rubyopen(cxt) do
      cxt.eval('1')
    end
        
    C::Context::GetCurrent().should be_nil    
  end
    
  it "does what now when we open a context twice from ruby?" do
    Context.open do |cxt|
      cxt.eval('1')      
    end
    C::Context::GetCurrent().should be_nil
  end
=end  
  def rubyopen(cxt, &block)
    native = cxt.instance_variable_get(:@native)
    if block_given?
      unless native == C::Context::GetCurrent()
        rputs "#{native} != #{C::Context::GetCurrent().inspect}"
        native.open do
          block.call(cxt)
        end
      else
        block.call(cxt)
      end
    end    
  end  
end
