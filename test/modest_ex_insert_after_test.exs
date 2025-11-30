defmodule ModestExInsertAfterTest do
  use ExUnit.Case
  # doctest ModestEx

  @tag :skip
  test "insert new html after selected node" do
    result = ModestEx.insert_after("<div><p>Hello</p></div>", "div p", "<p>World</p>")
    assert result == "<div><p>Hello</p><p>World</p></div>"
  end
end
