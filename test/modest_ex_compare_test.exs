defmodule ModestExCompareTest do
  use ExUnit.Case
  doctest ModestEx

  test "compare returns append" do
    result = ModestEx.compare("<div>Hello</div>", "<div>Hello<span>World</span></div>")
    assert result == [{:append, "html body div", "<span>World</span>"}]
  end

  test "compare returns set_attribute" do
    result = ModestEx.compare("<div>Hello</div>", "<div class=\"greeting\">Hello</div>")
    assert result == [{:set_attribute, "html body div", "class", "greeting"}]
  end

  test "compare returns mixed instructions" do
    result = ModestEx.compare("<div>Hello</div>", "<div class=\"greeting\">Hello<span>World</span></div>")
    assert result == [{:set_attribute, "html body div", "class", "greeting"}, {:append, "html body div", "<span>World</span>"}]
  end

  # test "compare complex strings" do
  #   result = ModestEx.compare("<p>Another</p>", "<div id=\"hello\">Hello<ul><li>World</li></ul></div><span>Other</span>")
  #   assert result == [{:set_tag, "html body p", "div"}, {:set_text, "html body div", "Hello"}, {:append, "html body div", "<ul><li>World</li></ul>"}, {:append, "html body", "<span>Other</span>"}]
  # end

  # test "compare empty with string" do
  #   result = ModestEx.compare("", "<p>Hello</p>")
  #   assert result == [{:append, "body", "<p>Hello</p>"}]
  # end

  # test "compare string with empty" do
  #   result = ModestEx.compare("<p>Hello</p>", "")
  #   assert result == [{:remove, "p"}]
  # end

  # test "compare two text nodes" do
  #   result = ModestEx.compare("Hello", "World")
  #   assert result == [{:set_text, "body", "World"}]
  # end

end
