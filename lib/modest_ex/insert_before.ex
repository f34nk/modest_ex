defmodule ModestEx.InsertBefore do
  @moduledoc false
  
  def insert_before([bin|rest], selector, new_bin) when is_bitstring(selector) when is_bitstring(new_bin) do
    [insert_before(bin, selector, new_bin)] ++ insert_before(rest, selector, new_bin)
  end

  def insert_before([], _, _), do: []
  
  def insert_before(bin, selector, new_bin) when is_bitstring(bin) when is_bitstring(selector) when is_bitstring(new_bin) do
    ModestEx.Safe.InsertBefore.insert_before(bin, selector, new_bin)
  end
end