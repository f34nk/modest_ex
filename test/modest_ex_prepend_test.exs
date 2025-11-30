defmodule ModestExPrependTest do
  use ExUnit.Case
  # doctest ModestEx

  @tag :skip
  test "prepend new html to html" do
    result = ModestEx.prepend("<div><p>World</p></div>", "div", "<p>Hello</p>")
    assert result == "<div><p>Hello</p><p>World</p></div>"
  end

  @tag :skip
  test "prepend new html to empty dom" do
    result =
      ModestEx.prepend("<html><head></head><body></body></html>", "body", "<p>Hello World</p>")

    assert result == "<p>Hello World</p>"
  end

  @tag :skip
  test "prepend new html to empty dom, too" do
    result = ModestEx.prepend("", "*", "<p>Hello World</p>")
    assert result == "<p>Hello World</p>"
  end
end
