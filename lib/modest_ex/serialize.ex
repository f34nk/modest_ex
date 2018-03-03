defmodule ModestEx.Serialize do
  
  def serialize([bin|rest]) do
    serialize(bin) ++ serialize(rest)
  end

  def serialize([]), do: []

  def serialize(bin) when is_bitstring(bin) do
    ModestEx.Safe.Serialize.serialize(bin)
  end

end