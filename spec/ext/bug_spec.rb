require File.dirname(__FILE__) + '/../spec_helper'

include V8

describe "A Javascript Object Reflected Into Ruby" do

  it "should not have a current context if no context is open" do
    cxt = C::Context.new
    cxt.open do
      rputs cxt.eval('"Hi There"', "<eval>")
      C::Context.new.open do |cxt2|
        rputs cxt2.eval('7 * 6', "<eval>")
      end
    end
    C::Context::GetCurrent().should be_nil
  end
  
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
