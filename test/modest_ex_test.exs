defmodule ModestExTest do
  use ExUnit.Case
  doctest ModestEx

  test "greets the world" do
    assert ModestEx.hello() == :world
  end
end
