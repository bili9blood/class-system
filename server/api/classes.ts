export default defineEventHandler(async () => {
  const classes = await useDatabase().class_.findMany({ select: { id: true, name: true } });
  return createResp(classes);
});
