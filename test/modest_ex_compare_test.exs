defmodule ModestExCompareTest do
  use ExUnit.Case
  doctest ModestEx

  test "compare returns append" do
    result = ModestEx.compare("<div>Hello</div>", "<div>Hello<span>World</span></div>")
    assert result == [{:append, "div", "<span>World</span>"}]
  end

  test "compare returns set_attribute" do
    result = ModestEx.compare("<div>Hello</div>", "<div class=\"greeting\">Hello</div>")
    assert result == [{:set_attribute, "div", "class", "greeting"}]
  end

  test "compare returns set_attribute and append" do
    result = ModestEx.compare("<div>Hello</div>", "<div class=\"greeting\">Hello<span>World</span></div>")
    assert result == [{:set_attribute, "div", "class", "greeting"}, {:append, "div", "<span>World</span>"}]
  end

end
