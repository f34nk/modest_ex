defmodule ModestExSliceTest do
  use ExUnit.Case
  doctest ModestEx

  test "slice html with selector" do
    result = ModestEx.slice("<h1>Lorem ipsum</h1><p>dolor sit amet</p><ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul><p>Sed ut perspiciatis</p><p>unde omnis iste natus</p>", "> *", 0, -1)
    assert result == ["<h1>Lorem ipsum</h1>", "<p>dolor sit amet</p>", "<ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul>", "<p>Sed ut perspiciatis</p>", "<p>unde omnis iste natus</p>"]
  end

end
