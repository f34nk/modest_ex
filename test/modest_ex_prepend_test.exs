defmodule ModestExPrependTest do
  use ExUnit.Case
  doctest ModestEx

  test "prepend new html to html" do
    result = ModestEx.prepend("<div><p>World</p></div>", "div", "<p>Hello</p>")
    assert result == "<html><head></head><body><div><p>Hello</p><p>World</p></div></body></html>"
  end

  test "prepend new html to empty dom" do
    result = ModestEx.prepend("<html><head></head><body></body></html>", "body", "<p>Hello World</p>")
    assert result == "<html><head></head><body><p>Hello World</p></body></html>"
  end

end
