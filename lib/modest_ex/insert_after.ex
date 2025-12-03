defmodule ModestEx.InsertAfter do
  @moduledoc false

  def insert_after([bin | rest], selector, new_bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    [insert_after(bin, selector, new_bin)] ++ insert_after(rest, selector, new_bin)
  end

  def insert_after([], _, _), do: []

  def insert_after(bin, selector, new_bin)
      when is_bitstring(bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    ModestEx.LexborHelper.ensure_started()

    scope = Application.get_env(:modest_ex, :scope, :body_children)

    with {:ok, doc} <- :lexbor_erl.parse(bin),
         {:ok, _num_matches} <- :lexbor_erl.insert_after_content(doc, selector, new_bin),
         {:ok, result} <- :lexbor_erl.serialize(doc),
         :ok <- :lexbor_erl.release(doc) do
      ModestEx.LexborHelper.apply_scope(result, scope)
    else
      {:error, _reason} = error ->
        error

      error ->
        {:error, error}
    end
  end
end
