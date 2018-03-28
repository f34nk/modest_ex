defmodule ModestExAppendTest do
  use ExUnit.Case
  doctest ModestEx

  test "can transform string" do
    result = ModestEx.transform("<div>Hello</div>", [{:set_attribute, "div", "class", "greeting"}, {:append, "div", "<span>World</span>"}, {:set_text, "div span", "Something"}, {:append, "body", "<p>Lorem ipsum</p>"}, {:remove, "p"}])
    assert result == "<div class=\"greeting\">Hello<span>Something</span></div>"
  end

end
