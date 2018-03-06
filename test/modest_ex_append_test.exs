defmodule ModestExAppendTest do
  use ExUnit.Case
  doctest ModestEx

  test "append new html to html" do
    result = ModestEx.append("<div><p>Hello</p></div>", "div", "<p>World</p>")
    assert result == "<html><head></head><body><div><p>Hello</p><p>World</p></div></body></html>"
  end

  test "append new html to empty dom" do
    result = ModestEx.append("<html><head></head><body></body></html>", "body", "<p>Hello World</p>")
    assert result == "<html><head></head><body><p>Hello World</p></body></html>"
  end

end
