defmodule ModestEx.Safe.Compare do
  @moduledoc false
  
  # defp decode(bin) when is_bitstring(bin) do
  #   decode(Jason.decode!(bin))
  # end

  defp decode(tuple) when is_tuple(tuple) do
    Tuple.insert_at(Tuple.delete_at(tuple, 0), 0, String.to_atom(elem(tuple, 0)))
  end

  # defp decode([list|rest]) when is_list(list) do
  #   [decode(List.to_tuple(list))] ++ decode(rest)
  # end


  defp decode(bin) when is_bitstring(bin) do
    result = ModestEx.split(bin)
    cond do
      is_bitstring(result) -> String.to_atom(result)
      is_list(result) -> decode(List.to_tuple(result))
    end
  end
  
  defp decode([]), do: []
  
  defp decode([bin|rest]) when is_bitstring(bin) do
    [decode(bin)] ++ decode(rest)
  end
  
  def compare(bin1, bin2) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:compare, bin1 <> "\0", bin2 <> "\0", ModestEx.scope() <> "\0"}) do
      {:ok, {:compare, result}} -> decode(result)
      _ -> {:error, "Failed to compare"}
    end
  end
  
end