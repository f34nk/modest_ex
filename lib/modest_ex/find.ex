defmodule ModestEx.Find do
  @moduledoc false
  
  def find([bin|rest], selector) when is_bitstring(selector) do
    find(bin, selector) ++ find(rest, selector)
  end

  def find([], _), do: []
  
  def find(bin, selector) when is_bitstring(bin) when is_bitstring(selector) do
    ModestEx.Safe.Find.find(bin, selector)
  end
  
end