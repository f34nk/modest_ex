defmodule ModestEx.Find do

  def find([bin|rest], selector) do
    find(bin, selector) ++ find(rest, selector)
  end

  def find([], _), do: []
  
  def find(bin, selector) when is_bitstring(bin) do
    ModestEx.Safe.Find.find(bin, selector)
  end
  
end