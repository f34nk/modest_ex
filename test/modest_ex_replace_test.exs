defmodule ModestExReplaceTest do
  use ExUnit.Case
  doctest ModestEx

  test "replace with new html" do
    result = ModestEx.replace("<div><p>Hello</p></div>", "div p", "<p>World</p>")
    assert result == "<html><head></head><body><div><p>World</p></div></body></html>"
  end

end
