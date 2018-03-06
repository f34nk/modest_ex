defmodule ModestEx.Replace do
  @moduledoc false
  
  def replace([bin|rest], selector, new_bin) when is_bitstring(selector) when is_bitstring(new_bin) do
    [replace(bin, selector, new_bin)] ++ replace(rest, selector, new_bin)
  end

  def replace([], _, _), do: []
  
  def replace(bin, selector, new_bin) when is_bitstring(bin) when is_bitstring(selector) when is_bitstring(new_bin) do
    ModestEx.Safe.Replace.replace(bin, selector, new_bin)
  end
end