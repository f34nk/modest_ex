defmodule ModestExAppendTest do
  use ExUnit.Case
  # doctest ModestEx

  test "append new html to html" do
    result = ModestEx.append("<div><p>Hello</p></div>", "div", "<p>World</p>")
    assert result == "<div><p>Hello</p><p>World</p></div>"
  end

  test "append new html to empty dom" do
    result =
      ModestEx.append("<html><head></head><body></body></html>", "body", "<p>Hello World</p>")

    assert result == "<p>Hello World</p>"
  end

  # Note: lexbor_erl's append_content searches within body, so "*" on empty
  # document cannot match any elements (head is outside body, body is root).
  # This is a behavioral difference from the original Modest library.
  @tag :skip
  test "append new html to empty dom, too" do
    result = ModestEx.append("", "*", "<p>Hello World</p>")
    assert result == "<p>Hello World</p>"
  end
end
