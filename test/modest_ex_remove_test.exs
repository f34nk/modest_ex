defmodule ModestExRemoveTest do
  use ExUnit.Case
  doctest ModestEx

  test "remove node from html" do
    result = ModestEx.remove("<div><p>Hello</p>World</div>", "div p")
    assert result == "<html><head></head><body><div>World</div></body></html>"
  end

end
