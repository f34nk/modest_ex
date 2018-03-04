defmodule ModestEx.Remove do
  @moduledoc false
  
  def remove([bin|rest], selector) when is_bitstring(selector) do
    remove(bin, selector) ++ remove(rest, selector)
  end

  def remove([], _), do: []
  
  def remove(bin, selector) when is_bitstring(bin) when is_bitstring(selector) do
    ModestEx.Safe.Remove.remove(bin, selector)
  end
end