defmodule ModestEx.Serialize do
  @moduledoc false

  def serialize([bin | rest], scope) do
    serialize(bin, scope) ++ serialize(rest, scope)
  end

  def serialize([], _), do: []

  def serialize(bin, scope) when is_bitstring(bin) when is_atom(scope) do
    ModestEx.Safe.Serialize.serialize(bin, scope)
  end
end
