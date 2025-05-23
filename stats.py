import pandas as pd

df = pd.read_csv("compression_results.csv")

HEADER_GZIP = 30
HEADER_RAR = 75
HEADER_XZ = 32

df["adj_gzip"] = df["gzip"] - HEADER_GZIP
df["adj_rar"] = df["rar"] - HEADER_RAR
df["adj_xz"] = df["xz"] - HEADER_XZ

df["gzip_compressed"] = df["adj_gzip"] < df["original"]
df["rar_compressed"] = df["adj_rar"] < df["original"]
df["xz_compressed"] = df["adj_xz"] < df["original"]

df["generator"] = df["file"].str.extract(r"test_data/([^/]+)/")[0]
df["length"] = df["file"].str.extract(r"_(\d+)_")[0].astype(int)

grouped = df.groupby(["generator", "length"]).agg({
    "gzip_compressed": "sum",
    "rar_compressed": "sum",
    "xz_compressed": "sum"
}).reset_index()

print("Сжатые файлы из 100 для каждой группы:")
print(grouped.rename(columns={
    "gzip_compressed": "GZIP",
    "rar_compressed": "RAR",
    "xz_compressed": "XZ"
}))
