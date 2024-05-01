import { access, unlink } from "node:fs/promises";
import { constants as fsConstants } from "node:fs";
import { execSync } from "node:child_process";
import { gt as semverGreaterThan } from "semver";

const LATEST_RELEASE_API_URL = "/repos/bili9blood/class-system/releases/latest";
const LATEST_DOWNLOAD_URL = `${import.meta.env.GITHUB_MIRROR ?? ""}https://github.com/bili9blood/class-system/releases/latest/download/class-system-display_windows-x86_64.zip`;
const CACHE_FILE = "__latest_cache.zip";

export default defineEventHandler(async () => {
  const current = await getCurrentVersion();
  const latest = await getLatestVersion();

  if (!semverGreaterThan(latest, current))
    return createResp(null, 304, "已是最新版本");

  if (!await downloadLatestFromGithub())
    return createResp(null, 500, "下载最新版本失败");

  const downloadUrl = await uploadLatestToKStore();
  if (!downloadUrl)
    return createResp(null, 500, "更新最新版本失败");

  if (!await updateDatabase(latest, downloadUrl))
    return createResp(null, 500, "更新数据库失败");

  return createResp(null);
});

async function getCurrentVersion() {
  const cur = (await $fetch("/api/version/latest")).data;
  return cur ? cur.version : "v0.0.0";
}

async function getLatestVersion() {
  try {
    const res = await requestGithubApi<{ tag_name?: string }>(LATEST_RELEASE_API_URL);
    return res.tag_name ?? "v0.0.0";
  }
  catch {
    return "v0.0.0";
  }
}

async function downloadLatestFromGithub() {
  try {
    execSync(`curl -o ${CACHE_FILE} ${LATEST_DOWNLOAD_URL}`);
    return true;
  }
  catch (e) { console.error(e); return false; }
}

async function uploadLatestToKStore() {
  try {
    await access(CACHE_FILE, fsConstants.R_OK);

    const kstoreToken = import.meta.env.KSTORE_TOKEN;

    const { id: fileId, downloadUrl } = (await $fetch<{ data: { id: number;downloadUrl: string } }>(
      "https://api.kstore.space/api/v1/file/search/path",
      {
        method: "POST",
        body: `access_token=${kstoreToken}&path=class-system-display_windows-x86_64.zip`,
        headers: { "Content-Type": "application/x-www-form-urlencoded" },
      },
    )).data;

    execSync(`curl https://upload.kstore.space/upload/${fileId}?access_token=${kstoreToken} -F "file=@${CACHE_FILE}"`);
    return downloadUrl;
  }
  catch (e) { console.error(e); return; }
  finally { await unlink(CACHE_FILE); }
}

async function updateDatabase(latest: string, downloadUrl: string) {
  const LATEST_VERSION_KEY = "latest_ver";
  const LATEST_DOWNLOAD_URL_KEY = "latest_url";

  const db = useDatabase();

  try {
    if (await db.key_value.findUnique({ where: { key: LATEST_VERSION_KEY } }))
      await db.key_value.update({ where: { key: LATEST_VERSION_KEY }, data: { value: latest } });
    else
      await db.key_value.create({ data: { key: LATEST_VERSION_KEY, value: latest } });

    if (await db.key_value.findUnique({ where: { key: LATEST_DOWNLOAD_URL_KEY } }))
      await db.key_value.update({ where: { key: LATEST_DOWNLOAD_URL_KEY }, data: { value: downloadUrl } });
    else
      await db.key_value.create({ data: { key: LATEST_DOWNLOAD_URL_KEY, value: downloadUrl } });
  }
  catch (e) { console.error(e); return false; }
  return true;
}
