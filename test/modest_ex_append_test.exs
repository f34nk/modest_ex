defmodule ModestExAppendTest do
  use ExUnit.Case
  doctest ModestEx

  test "append new html to html" do
    result = ModestEx.append("<div><p>Hello</p></div>", "div", "<p>World</p>")
    assert result == "<html><head></head><body><div><p>Hello</p><p>World</p></div></body></html>"
  end

end
