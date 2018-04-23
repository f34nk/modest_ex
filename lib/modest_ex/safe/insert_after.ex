defmodule ModestEx.Safe.InsertAfter do
  @moduledoc false

  def insert_after(bin, selector, new_bin) do
    case Nodex.Cnode.call(
           ModestEx.Safe.Cnode,
           {:insert_after, bin <> "\0", selector <> "\0", new_bin <> "\0",
            ModestEx.scope() <> "\0"}
         ) do
      {:ok, {:insert_after, result}} -> ModestEx.resolve(result)
      _ -> {:error, bin}
    end
  end
end
