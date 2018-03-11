defmodule ModestExPositionTest do
  use ExUnit.Case
  doctest ModestEx

  test "returns parsed positions" do
    result = ModestEx.position("<p>Hello</p><div></div><p>World</p>", "p")
    assert result == [1, 3]
  end

  test "returns single position" do
    result = ModestEx.position("<p>Hello</p><div></div><p>World</p>", "div")
    assert result == 2
  end

  test "returns no positions" do
    result = ModestEx.position("<p>Hello</p><div></div><p>World</p>", "h1")
    assert result == nil
  end

end
