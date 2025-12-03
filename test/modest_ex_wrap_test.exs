defmodule ModestExWrapTest do
  use ExUnit.Case
  # doctest ModestEx

  @tag :skip
  test "can wrap nodes" do
    result = ModestEx.wrap("<p>Hello</p><p>World</p>", "p", "<div></div>")
    assert result == "<div><p>Hello</p><p>World</p></div>"
  end
end
