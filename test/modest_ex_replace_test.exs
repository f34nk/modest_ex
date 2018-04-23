defmodule ModestExReplaceTest do
  use ExUnit.Case
  doctest ModestEx

  test "replace with new html" do
    result = ModestEx.replace("<div><p>Hello</p></div>", "div p", "<p>World</p>")
    assert result == "<div><p>World</p></div>"
  end
end
