defmodule ModestExPositionTest do
  use ExUnit.Case
  # doctest ModestEx

  @tag :skip
  test "returns parsed positions" do
    result = ModestEx.position("<p>Hello</p><div></div><p>World</p>", "p")
    assert result == [1, 3]
  end

  @tag :skip
  test "returns single position" do
    result = ModestEx.position("<p>Hello</p><div></div><p>World</p>", "div")
    assert result == [2]
  end

  # TODO: handle empty nodes
  # test "returns no positions" do
  #   result = ModestEx.position("<p>Hello</p><div></div><p>World</p>", "h1")
  #   assert result == {:error, "<p>Hello</p><div></div><p>World</p>"}
  # end
end
