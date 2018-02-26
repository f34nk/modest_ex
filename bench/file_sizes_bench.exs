defmodule CnodeFileSizesBench do
  use Benchfella
  alias Nodex.Cnode

  setup_all do
    Nodex.Distributed.up
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/gumbo_query_client"})
    contents = {
      pid,
      File.read!("bench/input/github_trending_js.html"),
      File.read!("bench/input/w3c_html5.html"),
      File.read!("bench/input/wikipedia_hyperlink.html")
    }
    {:ok, contents}
  end

  bench "github_trending_js.html 341k" do
    {pid, ref, _, _} = bench_context
    {:ok, reply} = Cnode.call(pid, {:find, ref, "h1"})
    # {:find, "<h1>\n      <a class=\"pagehead-heading\" href=\"/explore\">\n        Explore GitHub\n      </a>\n    </h1>"}
  end

  bench "w3c_html5.html 131k" do
    {pid, _, ref, _} = bench_context
    {:ok, reply} = Cnode.call(pid, {:find, ref, "h1"})
    # {:find, "<h1 id=\"big-title\">HTML5</h1>"}
  end

  bench "wikipedia_hyperlink.html 97k" do
    {pid, _, _, ref} = bench_context
    {:ok, reply} = Cnode.call(pid, {:find, ref, "h1"})
    # {:find, "<h1 id=\"firstHeading\" class=\"firstHeading\" lang=\"en\">Hyperlink</h1>"}
  end

end

