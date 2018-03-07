defmodule ModestExAppendTest do
  use ExUnit.Case
  doctest ModestEx

  test "append new html to html" do
    result = ModestEx.append("<div><p>Hello</p></div>", "div", "<p>World</p>")
    assert result == "<div><p>Hello</p><p>World</p></div>"
  end

  test "append new html to empty dom" do
    result = ModestEx.append("<html><head></head><body></body></html>", "body", "<p>Hello World</p>")
    assert result == "<p>Hello World</p>"
  end

  test "append new html to empty dom, too" do
    result = ModestEx.append("", "*", "<p>Hello World</p>")
    assert result == "<p>Hello World</p>"
  end

end
