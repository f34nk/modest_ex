defmodule ModestEx.Safe.Slice do
  @moduledoc false
  
  def slice(bin, selector, start_index, end_index) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:slice, bin <> "\0", selector <> "\0", start_index <> "\0", end_index <> "\0", ModestEx.delimiter() <> "\0"}) do
      {:ok, {:slice, result}} -> ModestEx.split(result)
      _ -> {:error, bin}
    end
  end
  
end