defmodule ModestExInsertBeforeTest do
  use ExUnit.Case
  # doctest ModestEx

  @tag :skip
  test "insert new html before selected node" do
    result = ModestEx.insert_before("<div><p>World</p></div>", "div p", "<p>Hello</p>")
    assert result == "<div><p>Hello</p><p>World</p></div>"
  end
end
