defmodule ModestExSliceTest do
  use ExUnit.Case
  doctest ModestEx

  test "slice html with selector from beginning to end" do
    result =
      ModestEx.slice(
        "<h1>Lorem ipsum</h1><p>dolor sit amet</p><ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul><p>Sed ut perspiciatis</p><p>unde omnis iste natus</p>",
        "body > *",
        0,
        -1
      )

    assert result == [
             "<h1>Lorem ipsum</h1>",
             "<p>dolor sit amet</p>",
             "<ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul>",
             "<p>Sed ut perspiciatis</p>",
             "<p>unde omnis iste natus</p>"
           ]
  end

  test "slice html with selector from beginning to list" do
    result =
      ModestEx.slice(
        "<h1>Lorem ipsum</h1><p>dolor sit amet</p><ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul><p>Sed ut perspiciatis</p><p>unde omnis iste natus</p>",
        "body > *",
        0,
        3
      )

    assert result == [
             "<h1>Lorem ipsum</h1>",
             "<p>dolor sit amet</p>",
             "<ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul>"
           ]
  end

  test "slice html with selector from list to end" do
    result =
      ModestEx.slice(
        "<h1>Lorem ipsum</h1><p>dolor sit amet</p><ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul><p>Sed ut perspiciatis</p><p>unde omnis iste natus</p>",
        "body > *",
        3,
        -1
      )

    assert result == ["<p>Sed ut perspiciatis</p>", "<p>unde omnis iste natus</p>"]
  end
end
