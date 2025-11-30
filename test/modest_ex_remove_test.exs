defmodule ModestExRemoveTest do
  use ExUnit.Case
  # doctest ModestEx

  @tag :skip
  test "remove node from html" do
    result = ModestEx.remove("<div><p>Hello</p>World</div>", "div p")
    assert result == "<div>World</div>"
  end
end
