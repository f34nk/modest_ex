defmodule ModestEx.Position do
  @moduledoc false

  def position([bin | rest], selector) do
    [position(bin, selector)] ++ position(rest, selector)
  end

  def position([], _), do: []

  def position(bin, selector) when is_bitstring(bin) when is_bitstring(selector) do
    ModestEx.Safe.Position.position(bin, selector)
  end
end
